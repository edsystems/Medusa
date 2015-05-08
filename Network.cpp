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

#include "Network.hpp"

//********************************************************************************
// [NetworkNode] Constructors:
//********************************************************************************

NetworkNode::NetworkNode() : priority_(-1), endpoint_() {}

//--------------------------------------------------------------------------------

NetworkNode::~NetworkNode() {}

//********************************************************************************
// [NetworkNode] Operators:
//********************************************************************************

bool NetworkNode::operator==(const NetworkNode & rhs) {
    return endpoint_ == rhs.endpoint_;
}

//--------------------------------------------------------------------------------

bool NetworkNode::operator!=(const NetworkNode & rhs) {
    return endpoint_ != rhs.endpoint_;
}

//********************************************************************************
// [NetworkNode] Properties:
//********************************************************************************

std::string NetworkNode::GetHost() const {
    return endpoint_->host_name();
}

//--------------------------------------------------------------------------------

std::string NetworkNode::GetService() const {
    return endpoint_->service_name();
}

//--------------------------------------------------------------------------------

std::string NetworkNode::GetAddress() const {
    return endpoint_->endpoint().address().to_string();
}

//--------------------------------------------------------------------------------

uint16_t NetworkNode::GetPort() const {
    return endpoint_->endpoint().port();
}

//********************************************************************************
// [NetworkNode] Methods:
//********************************************************************************

void NetworkNode::Initialize(const std::string & host, const std::string & service) {
    tcp::resolver resolver(Network::GetIoService());
    tcp::resolver::query query(host, service);
    endpoint_ = resolver.resolve(query);
}

//********************************************************************************
// [Network] Fields:
//********************************************************************************

boost::asio::io_service Network::ioService_;
std::vector<NetworkNode> Network::nodes_;

//********************************************************************************
// [Network] Methods:
//********************************************************************************

void Network::AddNode(const NetworkNode & victim) {
    if (!ContainsNode(victim)) {
        nodes_.push_back(victim);
    }
}

//--------------------------------------------------------------------------------

bool Network::ContainsNode(const NetworkNode & victim) {
    auto end = NodesEnd();
    return std::find(NodesBegin(), end, victim) != end;
}

//--------------------------------------------------------------------------------

Network::NodeIterator Network::FindNodeByHost(const std::string & value) {
    return std::find_if(NodesBegin(), NodesEnd(),
        [&value] (const NetworkNode & item) { return item.GetHost() == value; });
}

//--------------------------------------------------------------------------------

Network::NodeIterator Network::FindNodeByAddress(const std::string & value) {
    return std::find_if(NodesBegin(), NodesEnd(),
        [&value] (const NetworkNode & item) { return item.GetAddress() == value; });
}

//--------------------------------------------------------------------------------

Network::NodeIterator Network::FindNodeByPriority(int value) {
    return std::find_if(NodesBegin(), NodesEnd(),
        [&value] (const NetworkNode & item) { return item.GetPriority() == value; });
}

//--------------------------------------------------------------------------------

Network::NodeIterator Network::FindNodeByMaxPriority() {
    return std::max_element(
        NodesBegin(), NodesEnd(),
        [] (const NetworkNode & lhs, const NetworkNode & rhs) {
            return lhs.GetPriority() < rhs.GetPriority();
        }
    );
}

//--------------------------------------------------------------------------------

void Network::ClearNodes() {
    nodes_.clear();
}
