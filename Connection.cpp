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

//********************************************************************************
// Constants:
//********************************************************************************

#define NO_ADDRESS_VALUE ""
#define NO_PORT_VALUE 0

//********************************************************************************
// Constructors:
//********************************************************************************

Connection::Connection(SharedSocket & socket) :
    finished_(false), thread_(nullptr), socket_(socket) {}

//--------------------------------------------------------------------------------

Connection::~Connection() {}

//********************************************************************************
// Properties:
//********************************************************************************

std::string Connection::GetLocalAddress() const {
    return socket_ ? socket_->local_endpoint().address().to_string() : NO_ADDRESS_VALUE;
}

//--------------------------------------------------------------------------------

std::string Connection::GetRemoteAddress() const {
    return socket_ ? socket_->remote_endpoint().address().to_string() : NO_ADDRESS_VALUE;
}

//--------------------------------------------------------------------------------

uint16_t Connection::GetLocalPort() const {
    return socket_ ? socket_->local_endpoint().port() : NO_PORT_VALUE;
}

//--------------------------------------------------------------------------------

uint16_t Connection::GetRemotePort() const {
    return socket_ ? socket_->remote_endpoint().port() : NO_PORT_VALUE;
}
