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

#include "JobDescriptor.hpp"

#include <Message.hpp>

//********************************************************************************
// [JobDescriptor] Constructors:
//********************************************************************************

JobDescriptor::JobDescriptor() : identifier_(), ownerAddress_(), clientAddress_(),
    fileExtension_(), filePath_(), finalFilePath_(), fileSize_(0), numberOfFragments_(0),
    currentFragments_(0), filterId_(0), fileData_(Message::MAX_FRAGMENT_SIZE), texture_() {}

//--------------------------------------------------------------------------------

JobDescriptor::~JobDescriptor() {}

//--------------------------------------------------------------------------------

bool JobDescriptor::operator==(const JobDescriptor & rhs) {
    return identifier_ == rhs.identifier_ && clientAddress_ == rhs.clientAddress_;
}
