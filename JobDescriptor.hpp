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

#ifndef __MEDUSA_JOB_DESCRIPTOR__
#define __MEDUSA_JOB_DESCRIPTOR__

#include <JobIdentifier.hpp>
#include <FragmentedFile.hpp>
#include <Texture.hpp>

class JobDescriptor {
private:
    // Fields:
    JobIdentifier identifier_;
    std::string ownerAddress_;
    std::string clientAddress_;
    uint16_t clientPort_;
    std::string fileExtension_;
    std::string filePath_;
    std::string finalFilePath_;
    int32_t fileSize_;
    int32_t numberOfFragments_;
    int32_t currentFragments_;
    int16_t filterId_;
    FragmentedFile fileData_;
    Texture texture_;
public:
    // Constructors:
    JobDescriptor();
    ~JobDescriptor();
    bool operator==(const JobDescriptor & rhs);
    // Properties:
    inline const JobIdentifier & GetIdentifier() const { return identifier_; }
    inline const std::string & GetOwnerAddress() const { return ownerAddress_; }
    inline const std::string & GetClientAddress() const { return clientAddress_; }
    inline uint16_t GetClientPort() const { return clientPort_; }
    inline const std::string & GetFileExtension() const { return fileExtension_; }
    inline const std::string & GetFilePath() const { return filePath_; }
    inline const std::string & GetFinalFilePath() const { return finalFilePath_; }
    inline int32_t GetFileSize() const { return fileSize_; }
    inline int32_t GetNumberOfFragments() const { return numberOfFragments_; }
    inline int32_t GetCurrentFragments() const { return currentFragments_; }
    inline int16_t GetFilterId() const { return filterId_; }
    inline const FragmentedFile & GetFileData() const { return fileData_; }
    inline FragmentedFile & GetFileData() { return fileData_; }
    inline const Texture & GetTexture() const { return texture_; }
    inline Texture & GetTexture() { return texture_; }
    // Friends:
    friend class JobManager;
};

#endif
