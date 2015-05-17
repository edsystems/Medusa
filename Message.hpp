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

#ifndef __MEDUSA_MESSAGE__
#define __MEDUSA_MESSAGE__

#include <string>
#include <cstdint>
#include <boost/asio/ip/tcp.hpp>
#include <JobIdentifier.hpp>

//********************************************************************************
// Message:
//********************************************************************************

class Message {
public:
    // Constructors:
    Message() = delete;
    ~Message() = delete;

    // Constants:
    static const int MAX_SIZE                = 1024;
    static const int MAX_FRAGMENT_SIZE       = 1000;
    static const int MAX_FILE_EXTENSION_SIZE = 16;

    static const int8_t INVALID_ID           = 0;
    static const int8_t JOB_REQUEST_ID       = 1;
    static const int8_t JOB_ACCEPTED_ID      = 2;
    static const int8_t RECONNECT_REQUEST_ID = 3;
    static const int8_t FRAGMENT_SENT_ID     = 4;
    static const int8_t FRAGMENT_RECEIVED_ID = 5;
    static const int8_t JOB_STARTED_ID       = 6;
    static const int8_t JOB_FINISHED_ID      = 7;
    //static const int8_t TASK_REQUEST_ID      = 8;
    static const int8_t ERROR_RESPONSE_ID    = 101;

    static const int16_t ERROR_CODE_NOTHING_WRONG   = 0;
    static const int16_t ERROR_CODE_WRONG_EXTENSION = 1;
    static const int16_t ERROR_CODE_WRONG_FILTER    = 2;
    static const int16_t ERROR_CODE_WRONG_PARAMS    = 3;
    static const int16_t ERROR_CODE_WRONG_JOBID     = 4;
    static const int16_t ERROR_CODE_WRONG_FRAGMENT  = 5;
    //static const int16_t ERROR_CODE_ = 0;
    static const int16_t ERROR_CODE_PANIC           = 101;

    // Types:
    typedef boost::asio::ip::tcp::socket Socket;

    struct Generic {
        int8_t code;
    };

    struct JobRequest {
        int8_t code;
        char fileExtension[MAX_FILE_EXTENSION_SIZE];
        int32_t fileSize;
        int16_t filterId;
    };

    struct JobAccepted {
        int8_t code;
        JobIdentifier::DigestArray jobId;
    };

    struct ReconnectRequest {
        int8_t code;
        JobIdentifier::DigestArray jobId;
    };

    struct FragmentSent {
        int8_t code;
        int32_t fragmentNumber;
        int16_t fragmentDataSize;
        char fragmentData[MAX_FRAGMENT_SIZE];
    };

    typedef Generic FragmentReceived;

    typedef Generic JobStarted;

    struct JobFinished {
        int8_t code;
        char fileExtension[MAX_FILE_EXTENSION_SIZE];
        int32_t fileSize;
        int16_t filterId;
    };

    //...

    struct ErrorResponse {
        int8_t code;
        int16_t errorCode;
    };

    // Methods:
    static void BuildJobRequest(JobRequest & victim, const std::string & fileExt, int32_t fileSize, int16_t filterId);
    static void BuildJobAccepted(JobAccepted & victim, const JobIdentifier::DigestArrayParam jobId);
    static void BuildReconnectRequest(ReconnectRequest & victim, const JobIdentifier::DigestArrayParam jobId);
    static void BuildFragmentSent(FragmentSent & victim, int32_t number, size_t length, const char * data);
    static void BuildFragmentReceived(FragmentReceived & victim);
    static void BuildJobStarted(JobStarted & victim);
    static void BuildJobFinished(JobFinished & victim, const std::string & fileExt, int32_t fileSize, int16_t filterId);
    //...
    static void BuildErrorResponse(ErrorResponse & victim, int16_t errorCode);

    static bool SendJobRequest(Socket * socket, const std::string & fileExt, int32_t fileSize, int16_t filterId);
    static bool SendJobAccepted(Socket * socket, const JobIdentifier::DigestArrayParam jobId);
    static bool SendReconnectRequest(Socket * socket, const JobIdentifier::DigestArrayParam jobId);
    static bool SendFragmentSent(Socket * socket, int32_t number, size_t length, const char * data);
    static bool SendFragmentReceived(Socket * socket);
    static bool SendJobStarted(Socket * socket);
    static bool SendJobFinished(Socket * socket, const std::string & fileExt, int32_t fileSize, int16_t filterId);
    //...
    static bool SendErrorResponse(Socket * socket, int16_t errorCode);
};

#endif
