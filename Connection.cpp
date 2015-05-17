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

#include "Connection.hpp"

#include <iostream>
#include <boost/asio/write.hpp>
#include <boost/array.hpp>
#include <Message.hpp>
#include <Network.hpp>
#include <Utility.hpp>

//********************************************************************************
// [Connection] Constructors:
//********************************************************************************

Connection::Connection(SharedSocket & socket) :
    finished_(false), thread_(nullptr), socket_(socket) {}

//--------------------------------------------------------------------------------

Connection::~Connection() {}

//********************************************************************************
// [Connection] Properties:
//********************************************************************************

std::string Connection::GetLocalAddress() const {
    return socket_->local_endpoint().address().to_string();
}

//--------------------------------------------------------------------------------

std::string Connection::GetRemoteAddress() const {
    return socket_->remote_endpoint().address().to_string();
}

//--------------------------------------------------------------------------------

uint16_t Connection::GetLocalPort() const {
    return socket_->local_endpoint().port();
}

//--------------------------------------------------------------------------------

uint16_t Connection::GetRemotePort() const {
    return socket_->remote_endpoint().port();
}

//********************************************************************************
// [Connection] Methods:
//********************************************************************************

void Connection::logWriteLine(const std::string & line) {
#ifdef _DEBUG
    LogWriteLine("<" + GetRemoteAddress() + "> " + line);
#endif
}

//--------------------------------------------------------------------------------

bool Connection::isConnectionClosed(const boost::system::error_code & error) {
    return error == boost::asio::error::eof ||
           error == boost::asio::error::connection_reset;
}

//--------------------------------------------------------------------------------

void Connection::Run() {
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
                        logWriteLine("Connection closed");
                        finished_ = true;
                        return;
                    } else if (error) {
                        throw boost::system::system_error(error);
                    } else {
                        process(buffer.c_array(), length);
                    }
                }
                socket_->close();
            } catch (std::exception & e) {
                std::cerr << "[Connection::Run] catch => std::exception" << std::endl;
                std::cerr << "+ WHAT: " << e.what() << std::endl;
            }
            finished_ = true;
        }
    );
    thread_->detach();
}

//--------------------------------------------------------------------------------

Connection::SharedSocket Connection::MakeSharedSocket() {
    return std::make_shared<boost::asio::ip::tcp::socket>(Network::GetIoService());
}
