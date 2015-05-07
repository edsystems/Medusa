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

#ifndef __MEDUSA_CORE_MANAGER__
#define __MEDUSA_CORE_MANAGER__

#include <memory>
#include <string>
#include <cstdint>

class CoreManager {
private:
    // Singleton:
    CoreManager();
    static std::unique_ptr<CoreManager> instance_;
    // Fields:
    uint16_t listenPort_;
public:
    // Singleton:
    ~CoreManager();
    static CoreManager * Instance();
    static CoreManager & Reference();
    // Properties:
    inline uint16_t GetListenPort() { return listenPort_; }
    void SetListenPort(uint16_t value);
    // Methods:
    inline std::string GetListenPortAsString() const {
        return std::to_string(listenPort_);
    }
    void Initialize();
};

#endif