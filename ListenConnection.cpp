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

#include "ListenConnection.hpp"

#include <iostream>
#include <boost/asio/write.hpp>

//********************************************************************************
// Constructors:
//********************************************************************************

ListenConnection::ListenConnection(SharedSocket & socket) :
    Connection(socket) {}

//--------------------------------------------------------------------------------

ListenConnection::~ListenConnection() {}

//********************************************************************************
// Methods:
//********************************************************************************

void ListenConnection::Run() {
    //TODO: Complete this method...
    thread_ = std::make_shared<std::thread>(
        [&] () {
            //TODO: Test code...
            auto local_ep = socket_->local_endpoint();
            auto remote_ep = socket_->remote_endpoint();
            std::cout << "[LOCAL] " << local_ep.address() << " : " << local_ep.port() << std::endl;
            std::cout << "[REMOTE] " << remote_ep.address() << " : " << remote_ep.port() << std::endl;
            //...
            std::string message = "Hello, world!";
            boost::system::error_code ignored_error;
            boost::asio::write(*socket_, boost::asio::buffer(message), ignored_error);
            socket_->close();
            //...
            finished_ = true;
        }
    );
    thread_->detach();
    //...
}
