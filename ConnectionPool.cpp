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

#include "ConnectionPool.hpp"

//********************************************************************************
// [ConnectionPool] Fields:
//********************************************************************************

std::vector<ConnectionPool::SharedConnection> ConnectionPool::data_;

//********************************************************************************
// [ConnectionPool] Methods:
//********************************************************************************

void ConnectionPool::AddAndRun(SharedConnection & victim) {
    if (victim) {
        // Find a finished slot inside the pool:
        bool homeless = true;
        for (int i = 0, len = data_.size(); i < len; ++i) {
            if (data_[i]->IsFinished()) {
                data_[i] = victim;
                homeless = false;
                break;
            }
        }
        // If no finished slot, add a new one:
        if (homeless) {
            data_.push_back(victim);
        }
        // Run the connection thread:
        victim->Run();
    }
}

//--------------------------------------------------------------------------------

void ConnectionPool::ClearFinished() {
    data_.erase(
        std::remove_if(
            std::begin(data_), std::end(data_),
            [] (const SharedConnection & item) {
                return !item || item->IsFinished();
            }
        ),
        std::end(data_)
    );
}
