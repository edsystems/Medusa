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

//********************************************************************************
// [Message] Methods:
//********************************************************************************

bool Message::BuildJobRequest(JobRequest & victim, const std::string & fileExt,
    int32_t fileSize, int16_t filterId) {
    if (fileExt.length() < MAX_FILE_EXTENSION_SIZE - 1) {
        victim.code = JOB_REQUEST_ID;
        std::memcpy(victim.fileExtension, fileExt.c_str(), fileExt.length() + 1);
        victim.fileSize = fileSize;
        victim.filterId = filterId;
        return true;
    } else {
        return false;
    }
}
