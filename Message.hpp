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
    static const int MAX_FILE_EXTENSION_SIZE = 16;
    static const int MAX_FRAGMENT_SIZE       = 1000;

    static const int8_t JOB_REQUEST_ID       = 1;
    static const int8_t RECONNECT_REQUEST_ID = 2;
    static const int8_t SEND_FRAGMENT_ID     = 3;
    static const int8_t JOB_ACCEPTED_ID      = 4;
    static const int8_t JOB_FINISHED_ID      = 5;
    //static const int8_t TASK_REQUEST_ID      = 6;
    static const int8_t ERROR_RESPONSE_ID    = 101;

    static const int16_t ERROR_CODE_ANYTHING        = 0;
    static const int16_t ERROR_CODE_WRONG_EXTENSION = 1;
    static const int16_t ERROR_CODE_WRONG_FILTER    = 2;
    static const int16_t ERROR_CODE_WRONG_PARAMS    = 3;
    static const int16_t ERROR_CODE_WRONG_JOBID     = 4;
    static const int16_t ERROR_CODE_WRONG_FRAGMENT  = 5;
    //static const int16_t ERROR_CODE_ = 0;

    // Types:
    struct Generic {
        int8_t code;
    };

    struct JobRequest {
        int8_t code;
        char fileExtension[MAX_FILE_EXTENSION_SIZE];
        int32_t fileSize;
        int16_t filterId;
    };

    struct ReconnectRequest {
        int8_t code;
        int64_t jobId;
    };

    struct SendFragment {
        int8_t code;
        int32_t fragmentNumber;
        char fragmentData[MAX_FRAGMENT_SIZE];
    };

    struct JobAccepted {
        int8_t code;
        int64_t jobId;
    };

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
    static bool BuildJobRequest(JobRequest & victim, const std::string & fileExt, int32_t fileSize, int16_t filterId);
};

#endif
