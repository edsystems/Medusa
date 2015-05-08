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

#ifndef __MEDUSA_NETWORK__
#define __MEDUSA_NETWORK__

#include <vector>
#include <NetworkNode.hpp>

//********************************************************************************
// Network:
//********************************************************************************

class Network {
public:
    // Types:
    typedef std::vector<NetworkNode>::iterator NodeIterator;
private:
    // Fields:
    static boost::asio::io_service ioService_;
    static std::vector<NetworkNode> nodes_;
public:
    // Constructors:
    Network() = delete;
    ~Network() = delete;
    // Properties:
    inline static boost::asio::io_service & GetIoService() { return ioService_; }
    inline static std::vector<NetworkNode> & GetNodes() { return nodes_; }
    inline static NodeIterator NodesBegin() { return std::begin(nodes_); }
    inline static NodeIterator NodesEnd() { return std::end(nodes_); }
    // Methods:
    static void AddNode(const NetworkNode & victim);
    static bool ContainsNode(const NetworkNode & victim);
    static bool ContainsPriority(int victim);
    static NodeIterator FindNodeByHost(const std::string & value);
    static NodeIterator FindNodeByAddress(const std::string & value);
    static NodeIterator FindNodeByPriority(int value);
    static NodeIterator FindNodeByMaxPriority();
    static void ClearNodes();
};

#endif
