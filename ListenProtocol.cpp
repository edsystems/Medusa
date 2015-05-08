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

#include "ListenProtocol.hpp"

#include <boost/asio/write.hpp>

//********************************************************************************
// Constructors:
//********************************************************************************

ListenProtocol::ListenProtocol(SharedTcpSocket & socket) :
    finished_(false), thread_(nullptr), socket_(socket) {}

//********************************************************************************
// Methods:
//********************************************************************************

void ListenProtocol::Run() {
    //TODO: Complete this method...
    thread_ = std::make_shared<std::thread>(
        [&] () {
            finished_ = true;
            //TODO: Test code...
            std::string message = "Hello, world!";
            boost::system::error_code ignored_error;
            boost::asio::write(*socket_, boost::asio::buffer(message), ignored_error);
            //...
        }
    );
    thread_->detach();
    //...
}
