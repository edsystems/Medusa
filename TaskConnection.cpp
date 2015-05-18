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

#include "TaskConnection.hpp"

#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/array.hpp>
#include <JobManager.hpp>

//********************************************************************************
// [TaskConnection] Constructors:
//********************************************************************************

TaskConnection::TaskConnection(SharedSocket & socket) :
    Connection(socket), descriptor_(nullptr) {}

//--------------------------------------------------------------------------------

TaskConnection::~TaskConnection() {}

//********************************************************************************
// [TaskConnection] Methods:
//********************************************************************************

void TaskConnection::process(int8_t * buffer, size_t length) {
    /*
    switch (*buffer) {
    case Message::RECONNECT_REQUEST_ID:
        if (sizeof(Message::ReconnectRequest) == length) {
            auto * msg = (Message::ReconnectRequest *)buffer;
            //TODO: Complete this case...
            //...
        } else {
            throw std::runtime_error("[TaskConnection::process] Invalid ReconnectRequest size!");
        }
        break;
    }
    //*/
}

//--------------------------------------------------------------------------------

void TaskConnection::execute() {
    finished_ = false;
    try {
        //TODO: Complete this method...
    } catch (std::exception & e) {
        std::cerr << "[TaskConnection::execute] catch => std::exception" << std::endl;
        std::cerr << "+ WHAT: " << e.what() << std::endl;
    }
    logWriteLine("Job connection finished");
    finished_ = true;
}

//--------------------------------------------------------------------------------

void TaskConnection::Run() {
    thread_ = std::make_shared<std::thread>(&TaskConnection::execute, this);
    thread_->detach();
}
