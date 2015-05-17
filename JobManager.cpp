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
#include <Server.hpp>

//********************************************************************************
// [JobManager] Fields:
//********************************************************************************

std::mutex JobManager::mutex_;
std::vector<JobDescriptor> JobManager::descriptors_;

//********************************************************************************
// [JobManager] Methods:
//********************************************************************************

void JobManager::ClearDescriptors() {
    mutex_.lock();
    descriptors_.clear();
    mutex_.unlock();
}

//--------------------------------------------------------------------------------

bool JobManager::ValidateFileExtension(const std::string & value) {
    auto victim = value;
    std::transform(std::begin(victim), std::end(victim), std::begin(victim), ::tolower);
    return victim == "png" || victim == "jpg" || victim == "jpeg";
}

//--------------------------------------------------------------------------------

bool JobManager::ValidateFilterId(int16_t value) {
    return FILTER_ID_INVERT <= value && value <= FILTER_ID_GRAY;
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

//--------------------------------------------------------------------------------

JobDescriptor * JobManager::AddRequest(const std::string & address, uint16_t port,
    const Message::JobRequest & msg) {
    JobDescriptor * victim = nullptr;
    mutex_.lock();
    auto idx = descriptors_.size();
    descriptors_.push_back(JobDescriptor());
    victim = &(descriptors_[idx]);
    victim->identifier_.Generate(address);
    victim->ownerAddress_ = Server::LOCAL_HOST;
    victim->clientAddress_ = address;
    victim->clientPort_ = port;
    victim->fileExtension_ = std::string(msg.fileExtension);
    victim->filePath_ = victim->identifier_.ToString() + "." + victim->fileExtension_;
    victim->fileSize_ = msg.fileSize;
    victim->numberOfFragments_ = msg.fileSize / Message::MAX_FRAGMENT_SIZE;
    if (victim->numberOfFragments_ * Message::MAX_FRAGMENT_SIZE != msg.fileSize) {
        ++(victim->numberOfFragments_);
    }
    victim->currentFragments_ = 0;
    victim->filterId_ = msg.filterId;
    victim->fileData_.Make(victim->fileSize_, victim->identifier_.ToString() + "." + victim->fileExtension_);
    mutex_.unlock();
    return victim;
}

//--------------------------------------------------------------------------------

JobDescriptor * JobManager::FindRequest(const std::string & address, uint16_t port,
    Message::ReconnectRequest & msg) {
    JobDescriptor * victim = nullptr;
    mutex_.lock();
    JobIdentifier identifier(msg.jobId);
    auto item = std::find_if(
        std::begin(descriptors_), std::end(descriptors_),
        [&] (const JobDescriptor & item) {
            return item.GetClientAddress() == address && item.GetIdentifier() == identifier;
        }
    );
    if (item != std::end(descriptors_)) {
        victim = &(*item);
    }
    if (victim != nullptr) {
        victim->clientPort_ = port;
    }
    mutex_.unlock();
    return victim;
}
