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

#include "CoreManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <Options.hpp>
#include <Utility.hpp>

using boost::asio::ip::tcp;

//********************************************************************************
// Constants:
//********************************************************************************

const std::string CoreManager::LOCAL_HOST("localhost");
const int CoreManager::MAX_PRIORITY = 1000000;

//********************************************************************************
// Singleton:
//********************************************************************************

std::unique_ptr<CoreManager> CoreManager::instance_(nullptr);

//--------------------------------------------------------------------------------

CoreManager::CoreManager() : listenPort_(0), nodes_(), listenPool_() {}

//--------------------------------------------------------------------------------

CoreManager::~CoreManager() {}

//--------------------------------------------------------------------------------

CoreManager * CoreManager::Instance() {
    if (!instance_) {
        instance_.reset(new CoreManager());
    }
    return instance_.get();
}

//--------------------------------------------------------------------------------

CoreManager & CoreManager::Reference() {
    return *Instance();
}

//********************************************************************************
// Methods:
//********************************************************************************

void CoreManager::loadConfiguration(const std::string & path) {
    nodes_.clear();
    std::string line;
    std::ifstream file(path);
    while (std::getline(file, line)) {
        std::string address, port;
        std::stringstream sline(line);
        bool ok = std::getline(sline, address, ',') &&
                  std::getline(sline, port, ',') &&
                  IsPortNumber(port);
        if (ok) {
            nodes_.push_back(Node(address, port));
        } else {
            std::cerr << "[CoreManager::loadConfiguration] Wrong line!" << std::endl;
            std::cerr << "[FILE] " << path << std::endl;
            std::cerr << "[LINE] " << line << std::endl;
        }
    }
}

//--------------------------------------------------------------------------------

ListenProtocol & CoreManager::addListenThread(SharedTcpSocket & socket) {
    // Find a finished slot inside the pool:
    int index = -1;
    for (int i = 0, len = listenPool_.size(); i < len; ++i) {
        if (listenPool_[i].IsFinished()) {
            index = i;
            break;
        }
    }
    // If no finished slot, add a new one:
    if (index < 0) {
        listenPool_.push_back(ListenProtocol(socket));
    }
    // Return the listener thread:
    return listenPool_[index];
}

//--------------------------------------------------------------------------------

CoreManager::NodeIterator CoreManager::findNode(const std::string & address) {
    return std::find_if(std::begin(nodes_), std::end(nodes_),
        [&address] (const Node & item) { return item.address == address; });
}

//--------------------------------------------------------------------------------

int CoreManager::getRandomPriority() {
    int priority;
    NodeIterator killedByDeath, nodesEnd = std::end(nodes_);
    do {
        priority = GetRandom(MAX_PRIORITY);
        killedByDeath = std::find_if(std::begin(nodes_), nodesEnd,
            [&priority] (const Node & item) { return item.priority == priority; });
    } while(killedByDeath != nodesEnd);
    return priority;
}

//--------------------------------------------------------------------------------

void CoreManager::chooseLeader() {
}

//--------------------------------------------------------------------------------

void CoreManager::Run() {
    try {
        // Initialize the node configuration:
        auto & portNumber = Options::Get(Options::PortNumberKey);
        listenPort_ = static_cast<uint16_t>(std::stoi(portNumber));
        loadConfiguration(Options::Get(Options::ServersFileKey));
        // Add the local node to the table:
        nodes_.push_back(Node(LOCAL_HOST, portNumber));
        auto localNode = findNode(LOCAL_HOST);
        if (localNode != nodes_.end()) {
            localNode->priority = getRandomPriority();
        }
        // Initialize the node acceptor socket:
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), listenPort_));
        // Start the leader election:
        //TODO: Complete this code...
        //...
        // Main loop of the server:
        while (true) {
            // Accept a connection from outside:
            auto socket = std::make_shared<tcp::socket>(io_service);
            acceptor.accept(*socket);
            // Create a new thread with the listen protocol:
            addListenThread(socket).Run();
        }
    } catch (std::exception & e) {
        std::cerr << "[CoreManager::Run] catch => std::exception" << std::endl;
        std::cerr << "[WHAT] " << e.what() << std::endl;
    }
}
