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

#ifndef __MEDUSA_CONNECTION__
#define __MEDUSA_CONNECTION__

#include <memory>
#include <thread>
#include <string>
#include <cstdint>
#include <boost/asio/ip/tcp.hpp>

//********************************************************************************
// Connection:
//********************************************************************************

class Connection {
public:
    // Types:
    typedef std::shared_ptr<std::thread> SharedThread;
    typedef std::shared_ptr<boost::asio::ip::tcp::socket> SharedSocket;
protected:
    // Fields:
    bool finished_;
    SharedThread thread_;
    SharedSocket socket_;
    // Methods:
    void logWriteLine(const std::string & line);
public:
    // Constructors:
    Connection(SharedSocket & socket);
    virtual ~Connection();
    // Properties:
    inline bool IsFinished() const { return finished_; }
    inline bool HasThread() const { return thread_.get() != nullptr; }
    inline bool HasSocket() const { return socket_.get() != nullptr; }
    std::string GetLocalAddress() const;
    std::string GetRemoteAddress() const;
    uint16_t GetLocalPort() const;
    uint16_t GetRemotePort() const;
    // Methods:
    virtual void Run() = 0;
    static SharedSocket MakeSharedSocket();
};

#endif
