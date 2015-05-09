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

#ifndef __MEDUSA_JOB_MANAGER__
#define __MEDUSA_JOB_MANAGER__

#include <mutex>
#include <vector>
#include <Message.hpp>

class JobManager {
private:
    // Fields:
    static std::mutex mutex_;
public:
    // Constructors:
    JobManager() = delete;
    ~JobManager() = delete;
    // Properties:
    // Methods:
    static bool ValidateFileExtension(const std::string & value);
    static bool ValidateFilterId(int16_t value);
    static int16_t ValidateRequest(const Message::JobRequest & msg);
    static void AddRequest(const std::string & address, const Message::JobRequest & msg);
};

#endif