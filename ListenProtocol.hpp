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

#ifndef __MEDUSA_LISTEN_PROTOCOL__
#define __MEDUSA_LISTEN_PROTOCOL__

#include <thread>
#include <memory>
#include <boost/asio/ip/tcp.hpp>

typedef std::shared_ptr<std::thread> SharedThread;
typedef std::shared_ptr<boost::asio::ip::tcp::socket> SharedTcpSocket;

class ListenProtocol {
private:
    // Fields:
    bool finished_;
    SharedThread thread_;
    SharedTcpSocket socket_;
public:
    // Constructors:
    ListenProtocol(SharedTcpSocket & socket);
    // Properties:
    inline bool IsFinished() const { return finished_; }
    // Methods:
    void Run();
};

#endif
