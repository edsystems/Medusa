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
#include <boost/array.hpp>
#include <boost/asio/buffer.hpp>
#include <ConnectionPool.hpp>
#include <JobConnection.hpp>
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
                logWriteLine("Job request received");
                descriptor_ = JobManager::AddRequest(GetRemoteAddress(), GetRemotePort(), *msg);
                if (descriptor_) {
                    logWriteLine("Job created");
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
            throw std::runtime_error("[ListenConnection::process] Invalid JobRequest size!");
        }
        break;
    case Message::RECONNECT_REQUEST_ID:
        if (sizeof(Message::ReconnectRequest) == length) {
            auto * msg = (Message::ReconnectRequest *)buffer;
            descriptor_ = JobManager::FindRequest(GetRemoteAddress(), GetRemotePort(), *msg);
            if (descriptor_) {
                logWriteLine("Client reconnected");
                Message::SendReconnectAccepted(socket_.get());
            } else {
                Message::SendErrorResponse(socket_.get(), Message::ERROR_CODE_WRONG_JOBID);
            }
        } else {
            throw std::runtime_error("[ListenConnection::process] Invalid ReconnectRequest size!");
        }
        break;
    case Message::FRAGMENT_SENT_ID:
        if (sizeof(Message::FragmentSent) == length) {
            auto * msg = (Message::FragmentSent *)buffer;
            if (descriptor_) {
                logWriteLine("Fragment received");
                auto & fileData = descriptor_->GetFileData();
                if (fileData.Set(msg->fragmentNumber, msg->fragmentData, msg->fragmentDataSize)) {
                    logWriteLine("Fragment added to the file data");
                    if (msg->fragmentNumber + 1 == fileData.GetNumberOfChunks()) {
                        if (fileData.Validate()) {
                            logWriteLine("Job started");
                            fileData.Save();
                            ConnectionPool::AddAndRun<JobConnection>(socket_, descriptor_);
                            Message::SendJobStarted(socket_.get());
                            finished_ = true;
                        } else {
                            Message::SendErrorResponse(socket_.get(), Message::ERROR_CODE_WRONG_FILE_SENT);
                        }
                    } else {
                        logWriteLine("Send fragment received confirmation");
                        Message::SendFragmentReceived(socket_.get());
                    }
                } else {
                    Message::SendErrorResponse(socket_.get(), Message::ERROR_CODE_WRONG_FRAGMENT);
                }
            } else {
                Message::SendErrorResponse(socket_.get(), Message::ERROR_CODE_PANIC);
            }
        } else {
            throw std::runtime_error("[ListenConnection::process] Invalid FragmentSent size!");
        }
        break;
    //case Message::_ID:
        //TODO: Complete this case...
        //...
    }
}

//--------------------------------------------------------------------------------

void ListenConnection::execute() {
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
        std::cerr << "[ListenConnection::execute] catch => std::exception" << std::endl;
        std::cerr << "+ WHAT: " << e.what() << std::endl;
    }
    logWriteLine("Listen connection finished");
    finished_ = true;
}

//--------------------------------------------------------------------------------

void ListenConnection::Run() {
    thread_ = std::make_shared<std::thread>(&ListenConnection::execute, this);
    thread_->detach();
}
