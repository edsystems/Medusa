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

#define _CRT_SECURE_NO_WARNINGS
#include "JobIdentifier.hpp"

#include <ctime>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <boost/uuid/sha1.hpp>
#include <Utility.hpp>

//********************************************************************************
// [JobIdentifier] Constructors:
//********************************************************************************

JobIdentifier::JobIdentifier() {
    memset(hash_, 0, sizeof(DigestArray));
}

//--------------------------------------------------------------------------------

JobIdentifier::JobIdentifier(const DigestArrayParam hash) {
    memcpy(hash_, hash, sizeof(DigestArray));
}

//--------------------------------------------------------------------------------

JobIdentifier::~JobIdentifier() {}

//--------------------------------------------------------------------------------

bool JobIdentifier::operator==(const JobIdentifier & rhs) const {
    return Equals(rhs);
}

//********************************************************************************
// [JobIdentifier] Properties:
//********************************************************************************

void JobIdentifier::GetHash(DigestArrayParam hash) const {
    memcpy(hash, hash_, sizeof(DigestArray));
}

//********************************************************************************
// [JobIdentifier] Methods:
//********************************************************************************

bool JobIdentifier::Equals(const JobIdentifier & rhs) const {
    return memcmp(rhs.hash_, hash_, sizeof(DigestArray)) == 0;
}

//--------------------------------------------------------------------------------

bool JobIdentifier::Equals(const DigestArrayParam hash) const {
    return memcmp(hash, hash_, sizeof(DigestArray)) == 0;
}

//--------------------------------------------------------------------------------

void JobIdentifier::Generate(const std::string & address) {
    // Generate the data to be used in the hash:
    auto now = std::chrono::system_clock::now();
    auto nowInMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    auto rawTime = std::chrono::system_clock::to_time_t(now);
    // GCC doesn't have put_time, THANKS!
    //auto formatedTime = std::put_time(gmtime(&rawTime), " %Y-%m-%d %H:%M:%S.");
    const size_t MAX_FORMATED_TIME = 128;
    char formatedTime[MAX_FORMATED_TIME];
    formatedTime[0] = '\0';
    strftime(formatedTime, MAX_FORMATED_TIME, " %Y-%m-%d %H:%M:%S.", gmtime(&rawTime));
    auto ms = nowInMs.count() % 1000;
    std::stringstream buffer;
    buffer << address << formatedTime << std::setfill('0') << std::setw(3) << ms;
    std::string data(buffer.str());
    // Generate the SHA1 hash value:
    boost::uuids::detail::sha1 converter;
    converter.process_bytes(data.c_str(), data.size());
    converter.get_digest(hash_);
}

//--------------------------------------------------------------------------------

std::string JobIdentifier::ToString() const {
    std::stringstream buffer;
    buffer << std::hex;
    std::for_each(std::begin(hash_), std::end(hash_),
        [&] (uint32_t value) { buffer << value; });
    return buffer.str();
}
