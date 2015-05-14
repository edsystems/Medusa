//********************************************************************************
// Medusa, a distributed embedded system to apply filters on image files.
// Copyright (C) 2015  Gorka Su�rez Garc�a, Dan Cristian Rotaru
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
#include <boost/array.hpp>
#include <JobManager.hpp>

//********************************************************************************
// [ListenConnection] Constructors:
//********************************************************************************

ListenConnection::ListenConnection(SharedSocket & socket) :
    Connection(socket), descriptor_(nullptr) {}

//--------------------------------------------------------------------------------

ListenConnection::~ListenConnection() {}

//********************************************************************************
// [ListenConnection] Methods:
//********************************************************************************

void ListenConnection::process(int8_t * buffer, size_t length) {
    switch (*buffer) {
    case Message::JOB_REQUEST_ID:
        if (sizeof(Message::JobRequest) == length) {
            auto * msg = (Message::JobRequest *)buffer;
            auto errorCode = JobManager::ValidateRequest(*msg);
            if (errorCode == Message::ERROR_CODE_NOTHING_WRONG) {
                logWriteLine("Job request received.");
                descriptor_ = JobManager::AddRequest(GetRemoteAddress(), *msg);
                if (descriptor_) {
                    logWriteLine("Job created.");
                    JobIdentifier::DigestArray jobId;
                    descriptor_->GetIdentifier().GetHash(jobId);
                    Message::SendJobAccepted(socket_.get(), jobId);
                } else {
                    Message::SendErrorResponse(socket_.get(), Message::ERROR_CODE_PANIC);
                }
            } else {
                Message::SendErrorResponse(socket_.get(), errorCode);
            }
        } else {
            throw std::exception("[ListenConnection::process] Invalid JobRequest size!");
        }
        break;
    //TODO: Complete this method...
    //...
    }
}

//--------------------------------------------------------------------------------

void ListenConnection::Run() {
    thread_ = std::make_shared<std::thread>(
        [&] () {
            try {
                bool notExit = true;
                boost::system::error_code error;
                boost::array<int8_t, Message::MAX_SIZE> buffer;
                auto socketBuffer = boost::asio::buffer(buffer);
                while (notExit) {
                    size_t length = socket_->read_some(socketBuffer, error);
                    if (error == boost::asio::error::eof) {
                        logWriteLine("Connection closed.");
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
                std::cerr << "[ListenConnection::Run] catch => std::exception" << std::endl;
                std::cerr << "[WHAT] " << e.what() << std::endl;
            }
            finished_ = true;
        }
    );
    thread_->detach();
}
