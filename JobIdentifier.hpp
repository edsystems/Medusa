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

#ifndef __MEDUSA_JOB_IDENTIFIER__
#define __MEDUSA_JOB_IDENTIFIER__

#include <string>
#include <cstdint>

class JobIdentifier {
public:
    // Constants:
    static const int DIGEST_SIZE = 5;
    // Types:
    typedef uint32_t DigestArray[DIGEST_SIZE];
    typedef uint32_t (&DigestArrayParam)[DIGEST_SIZE];
private:
    // Fields:
    DigestArray hash_;
public:
    // Constructors:
    JobIdentifier();
    JobIdentifier(DigestArrayParam hash);
    ~JobIdentifier();
    // Properties:
    inline const uint32_t * GetHash() const { return hash_; }
    void GetHash(DigestArrayParam hash) const;
    // Methods:
    bool Equals(DigestArrayParam hash) const;
    void Generate(const std::string & address);
    std::string ToString() const;
};

#endif
