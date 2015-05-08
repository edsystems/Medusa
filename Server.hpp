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

#ifndef __MEDUSA_SERVER__
#define __MEDUSA_SERVER__

#include <string>
#include <cstdint>

//********************************************************************************
// Server:
//********************************************************************************

class Server {
public:
    // Constants:
    static const std::string LOCAL_HOST;
private:
    // Fields:
    static uint16_t port_;
    // Methods:
    static void loadServers(const std::string & path);
public:
    // Constructors:
    Server() = delete;
    ~Server() = delete;
    // Properties:
    inline static uint16_t GetPort() { return port_; }
    // Methods:
    static bool Initialize();
    static int GetNotUsedPriority();
    static void Run();
};

#endif
