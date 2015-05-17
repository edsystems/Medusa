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

#include "JobConnection.hpp"

#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/array.hpp>
#include <JobManager.hpp>

//********************************************************************************
// [JobConnection] Constructors:
//********************************************************************************

JobConnection::JobConnection(SharedSocket & socket) :
    Connection(socket), descriptor_(nullptr) {}

//--------------------------------------------------------------------------------

JobConnection::~JobConnection() {}

//********************************************************************************
// [JobConnection] Methods:
//********************************************************************************

void JobConnection::process(int8_t * buffer, size_t length) {
    /*
    switch (*buffer) {
    case Message::RECONNECT_REQUEST_ID:
        if (sizeof(Message::ReconnectRequest) == length) {
            auto * msg = (Message::ReconnectRequest *)buffer;
            //TODO: Complete this case...
            //...
        } else {
            throw std::exception("[JobConnection::process] Invalid ReconnectRequest size!");
        }
        break;
    }
    //*/
}

//--------------------------------------------------------------------------------

void JobConnection::Run() {
    /*
    thread_ = std::make_shared<std::thread>(
        [&] () {
            finished_ = false;
            try {
                boost::system::error_code error;
                boost::array<int8_t, Message::MAX_SIZE> buffer;
                auto socketBuffer = boost::asio::buffer(buffer);
                while (!finished_) {
                    size_t length = socket_->read_some(socketBuffer, error);
                    if (isConnectionClosed(error)) {
                        logWriteLine("Listen connection closed");
                        finished_ = true;
                        return;
                    } else if (error) {
                        throw boost::system::system_error(error);
                    } else {
                        process(buffer.c_array(), length);
                    }
                }
            } catch (std::exception & e) {
                std::cerr << "[JobConnection::Run] catch => std::exception" << std::endl;
                std::cerr << "+ WHAT: " << e.what() << std::endl;
            }
            logWriteLine("Listen connection finished");
            finished_ = true;
        }
    );
    thread_->detach();
    //*/
}
