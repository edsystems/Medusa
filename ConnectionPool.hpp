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

#ifndef __MEDUSA_CONNECTION_POOL__
#define __MEDUSA_CONNECTION_POOL__

#include <vector>
#include <Connection.hpp>

//********************************************************************************
// ConnectionPool:
//********************************************************************************

class ConnectionPool {
public:
    // Types:
    typedef std::shared_ptr<Connection> SharedConnection;
protected:
    // Fields:
    static std::vector<SharedConnection> data_;
public:
    // Constructors:
    ConnectionPool() = delete;
    ~ConnectionPool() = delete;
    // Properties:
    inline static int Count() { return data_.size(); }
    // Methods:
    static void AddAndRun(SharedConnection & victim);
    static void ClearFinished();
    // Templates:
    template<typename T> inline
    static void AddAndRun(Connection::SharedSocket & socket) {
        AddAndRun(SharedConnection(new T(socket)));
    }
    template<typename T, typename U> inline
    static void AddAndRun(Connection::SharedSocket & socket, U param) {
        AddAndRun(SharedConnection(new T(socket, param)));
    }
};

#endif
