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
#include <Network.hpp>
#include <Options.hpp>
#include <Utility.hpp>
#include <Server.hpp>
#include <ListenConnection.hpp>
#include <ConnectionPool.hpp>

using boost::asio::ip::tcp;

//********************************************************************************
// Singleton:
//********************************************************************************

//TODO: Delete this class...
std::unique_ptr<CoreManager> CoreManager::instance_(nullptr);
CoreManager * CoreManager::Instance() {
    if (!instance_) { instance_.reset(new CoreManager()); }
    return instance_.get();
}
//...

//********************************************************************************
// Methods:
//********************************************************************************

void CoreManager::Run() {
    try {
        // Initialize the node acceptor socket:
        tcp::acceptor acceptor(Network::GetIoService(), tcp::endpoint(tcp::v4(), Server::GetPort()));
        // Start the leader election:
        //TODO: Complete this code...
        //...
        // Main loop of the server:
        while (true) {
            // Accept a connection from outside:
            auto socket = Connection::MakeSharedSocket();
            acceptor.accept(*socket);
            // Create a new thread with the listen protocol:
            ConnectionPool::AddAndRun<ListenConnection>(socket);
        }
    } catch (std::exception & e) {
        std::cerr << "[CoreManager::Run] catch => std::exception" << std::endl;
        std::cerr << "[WHAT] " << e.what() << std::endl;
    }
}
