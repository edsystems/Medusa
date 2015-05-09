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

#include "Message.hpp"

#include <boost/asio/write.hpp>

//********************************************************************************
// Functions:
//********************************************************************************

template <typename T> inline
bool SendMessage(Message::Socket * socket, T & message) {
    boost::system::error_code systemError;
    auto buffer = boost::asio::buffer(&message, sizeof(T));
    boost::asio::write(*socket, buffer, systemError);
    return !systemError;
}

//********************************************************************************
// [Message] Methods:
//********************************************************************************

void Message::BuildJobRequest(JobRequest & victim, const std::string & fileExt,
    int32_t fileSize, int16_t filterId) {
    auto fileExtLength = fileExt.length() + 1;
    if (fileExtLength < MAX_FILE_EXTENSION_SIZE) {
        victim.code = JOB_REQUEST_ID;
        std::memcpy(victim.fileExtension, fileExt.c_str(), fileExtLength);
        victim.fileSize = fileSize;
        victim.filterId = filterId;
    } else {
        victim.code = INVALID_ID;
    }
}

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

void Message::BuildErrorResponse(ErrorResponse & victim, int16_t errorCode) {
    if (errorCode > ERROR_CODE_NOTHING_WRONG) {
        victim.code = ERROR_RESPONSE_ID;
        victim.errorCode = errorCode;
    } else {
        victim.code = INVALID_ID;
    }
}

//--------------------------------------------------------------------------------

bool Message::SendJobRequest(Socket * socket, const std::string & fileExt,
    int32_t fileSize, int16_t filterId) {
    // Make the message:
    JobRequest message;
    BuildJobRequest(message, fileExt, fileSize, filterId);
    if (message.code != JOB_REQUEST_ID) return false;
    // Send the message:
    return SendMessage(socket, message);
}

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

bool Message::SendErrorResponse(Socket * socket, int16_t errorCode) {
    // Make the message:
    ErrorResponse message;
    BuildErrorResponse(message, errorCode);
    if (message.code != ERROR_RESPONSE_ID) return false;
    // Send the message:
    return SendMessage(socket, message);
}
