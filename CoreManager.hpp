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

#ifndef __MEDUSA_CORE_MANAGER__
#define __MEDUSA_CORE_MANAGER__

#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <ListenProtocol.hpp>

class CoreManager {
public:
    // Types:
    struct Node {
        std::string address, port; int priority;
        Node(const std::string & ad, const std::string & po) :
            address(ad), port(po), priority(-1) {}
    };
    // Constants:
    static const std::string LOCAL_HOST;
    static const int MAX_PRIORITY;
private:
    // Types:
    typedef std::vector<Node>::iterator NodeIterator;
    // Singleton:
    CoreManager();
    static std::unique_ptr<CoreManager> instance_;
    // Fields:
    uint16_t listenPort_;
    std::vector<Node> nodes_;
    std::vector<ListenProtocol> listenPool_;
    // Methods:
    void loadConfiguration(const std::string & path);
    ListenProtocol & addListenThread(SharedTcpSocket & socket);
    NodeIterator findNode(const std::string & address);
    int getRandomPriority();
    void chooseLeader();
public:
    // Singleton:
    ~CoreManager();
    static CoreManager * Instance();
    static CoreManager & Reference();
    // Properties:
    inline uint16_t GetListenPort() { return listenPort_; }
    inline std::vector<Node> & GetNodes() { return nodes_; }
    inline std::string GetListenPortAsString() const {
        return std::to_string(listenPort_);
    }
    // Methods:
    void Run();
};

#endif
