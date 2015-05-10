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

#include "JobManager.hpp"

#include <algorithm>

//********************************************************************************
// [JobManager] Fields:
//********************************************************************************

std::mutex JobManager::mutex_;

//********************************************************************************
// [JobManager] Methods:
//********************************************************************************

bool JobManager::ValidateFileExtension(const std::string & value) {
    auto victim = value;
    std::transform(std::begin(victim), std::end(victim), std::begin(victim), ::tolower);
    return victim == "png" || victim == "jpg" || victim == "jpeg";
}

//--------------------------------------------------------------------------------

bool JobManager::ValidateFilterId(int16_t value) {
    //TODO: Complete this method...
    return true;
    //...
}

//--------------------------------------------------------------------------------

int16_t JobManager::ValidateRequest(const Message::JobRequest & msg) {
    if (!ValidateFileExtension(std::string(msg.fileExtension))) {
        return Message::ERROR_CODE_WRONG_EXTENSION;
    } else if (!ValidateFilterId(msg.filterId)) {
        return Message::ERROR_CODE_WRONG_FILTER;
    } else {
        return Message::ERROR_CODE_NOTHING_WRONG;
    }
}
