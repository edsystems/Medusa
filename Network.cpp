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
    return std::find(NodesBegin(), NodesEnd(), victim) != NodesEnd();
}

//--------------------------------------------------------------------------------

bool Network::ContainsPriority(int victim) {
    return FindNodeByPriority(victim) != NodesEnd();
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
