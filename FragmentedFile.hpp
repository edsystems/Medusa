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

#ifndef __MEDUSA_FRAGMENTED_FILE__
#define __MEDUSA_FRAGMENTED_FILE__

#include <string>
#include <vector>
#include <cstdint>

class FragmentedFile {
public:
    // Types:
    typedef std::vector<uint8_t> FileChunk;
    typedef std::vector<FileChunk> VectorOfChunks;
private:
    // Fields:
    size_t size_;
    size_t chunkSize_;
    VectorOfChunks data_;
    std::string path_;
public:
    // Constructors:
    FragmentedFile(size_t chunkSize);
    FragmentedFile(const FragmentedFile & obj);
    ~FragmentedFile();
    // Properties:
    inline size_t GetSize() const { return size_; }
    inline size_t GetChunkSize() const { return chunkSize_; }
    inline unsigned int GetNumberOfChunks() const { return data_.size(); }
    inline const std::string & GetPath() const { return path_; }
    std::string GetPathExtension() const;
    // Methods:
    bool Load(const std::string & path);
    bool Save(const std::string & path);
    void Unload();
};

#endif
