//********************************************************************************
// Medusa, a distributed embedded system to apply filters on image files.
// Copyright (C) 2015  Gorka Suárez García, Dan Cristian Rotaru
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//********************************************************************************

#include "Server.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <ListenConnection.hpp>
#include <ConnectionPool.hpp>
#include <Network.hpp>
#include <Options.hpp>
#include <Utility.hpp>

using boost::asio::ip::tcp;

//********************************************************************************
// [Server] Constants:
//********************************************************************************

const std::string Server::LOCAL_HOST("localhost");

//********************************************************************************
// [Server] Fields:
//********************************************************************************

uint16_t Server::port_ = 0;

//********************************************************************************
// [Server] Methods:
//********************************************************************************

void Server::loadServers(const std::string & path) {
    // The add server lambda function:
    auto addServer = [] (const std::string & host, const std::string & service) {
        try {
            NetworkNode node;
            node.Initialize(host, service);
            Network::AddNode(node);
        } catch (std::exception & e) {
            std::cerr << "[Server::loadServers::addServer] catch => std::exception" << std::endl;
            std::cerr << "+ WHAT: " << e.what() << std::endl;
        }
    };
    // Clear the current nodes:
    Network::ClearNodes();
    // Add the local node to the table:
    auto & portNumber = Options::Get(Options::PortNumberKey);
    addServer(LOCAL_HOST, portNumber);
    // Load the lines inside the servers configuration file:
    std::string line, address, port;
    std::ifstream file(path);
    while (std::getline(file, line)) {
        // This is a Comma-separated values file:
        std::stringstream sline(line);
        bool ok = std::getline(sline, address, ',') &&
                  std::getline(sline, port, ',') &&
                  IsPortNumber(port);
        if (ok) {
            addServer(address, port);
        } else {
            std::cerr << "[Server::loadServers] Wrong line!" << std::endl;
            std::cerr << "+ FILE: " << path << std::endl;
            std::cerr << "+ LINE: " << line << std::endl;
        }
    }
}

//--------------------------------------------------------------------------------

bool Server::Initialize() {
    try {
        // Initialize the random number generation:
        InitializeRandom();
        // Initialize the port to use in the server:
        auto & portNumber = Options::Get(Options::PortNumberKey);
        port_ = static_cast<uint16_t>(std::stoi(portNumber));
        // Initialize the network node table:
        loadServers(Options::Get(Options::ServersFileKey));
        return true;
    } catch (std::exception & e) {
        std::cerr << "[Server::Initialize] catch => std::exception" << std::endl;
        std::cerr << "+ WHAT: " << e.what() << std::endl;
        return false;
    }
}

//--------------------------------------------------------------------------------

int Server::GetNotUsedPriority() {
    int priority;
    do {
        priority = GetRandom();
    } while(Network::ContainsPriority(priority));
    return priority;
}

//--------------------------------------------------------------------------------

void Server::Run() {
    try {
        // Initialize the node acceptor socket:
        tcp::acceptor acceptor(Network::GetIoService(), tcp::endpoint(tcp::v4(), Server::GetPort()));
        // Main loop of the server:
        while (true) {
            // Accept a connection from outside:
            auto socket = Connection::MakeSharedSocket();
            acceptor.accept(*socket);
            // Create a new thread with the listen protocol:
            ConnectionPool::AddAndRun<ListenConnection>(socket);
        }
    } catch (std::exception & e) {
        std::cerr << "[Server::Run] catch => std::exception" << std::endl;
        std::cerr << "+ WHAT: " << e.what() << std::endl;
    }
}
