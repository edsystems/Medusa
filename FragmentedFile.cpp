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

#include "FragmentedFile.hpp"

#include <fstream>
#include <algorithm>

//********************************************************************************
// [FragmentedFile] Constructors:
//********************************************************************************

FragmentedFile::FragmentedFile(size_t chunkSize) :
    size_(0), chunkSize_(chunkSize), data_(), path_() {}

//--------------------------------------------------------------------------------

FragmentedFile::FragmentedFile(const FragmentedFile & obj) :
    size_(obj.size_), chunkSize_(obj.chunkSize_), data_(obj.data_),
    path_(obj.path_) {}

//--------------------------------------------------------------------------------

FragmentedFile::~FragmentedFile() {
    Unload();
}

//********************************************************************************
// [FragmentedFile] Properties:
//********************************************************************************

std::string FragmentedFile::GetPathExtension() const {
    auto begin = path_.size() - 1;
    for (unsigned int i = begin; i >= 0; --i) {
        char item = path_[i];
        if (item == '.') {
            return i < begin ? path_.substr(i + 1) : "";
        } else if (item == '/' || item == '\\') {
            break;
        }
    }
    return "";
}

//********************************************************************************
// [FragmentedFile] Methods:
//********************************************************************************

bool FragmentedFile::Load(const std::string & path) {
    // Open a file for input:
    std::fstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) return false;
    // Load the a file in fragmented chunks:
    Unload();
    path_ = path;
    auto addChunk = [&] () {
        data_.push_back(FileChunk());
        auto last = data_.rbegin();
        last->reserve(chunkSize_);
        return last;
    };
    char buffer;
    auto last = addChunk();
    while (!file.eof()) {
        file.read(&buffer, sizeof(char));
        if (file.good()) {
            if (last->size() >= chunkSize_) {
                last = addChunk();
            }
            last->push_back(buffer);
            ++size_;
        }
    }
    file.close();
    return true;
}

//--------------------------------------------------------------------------------

bool FragmentedFile::Save(const std::string & path) {
    // Open a file for output:
    std::fstream file;
    file.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!file.is_open()) return false;
    // Save the fragmented chunks in a file:
    std::for_each(
        std::begin(data_), std::end(data_),
        [&file] (const FileChunk & victim) {
            file.write((const char *)victim.data(), victim.size());
        }
    );
    file.close();
    return true;
}

//--------------------------------------------------------------------------------

void FragmentedFile::Unload() {
    std::for_each(std::begin(data_), std::end(data_),
        [] (FileChunk & victim) { victim.clear(); });
    data_.clear();
    path_ = "";
    size_ = 0;
}
