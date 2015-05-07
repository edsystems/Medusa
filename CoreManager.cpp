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

#include "CoreManager.hpp"

#include <Options.hpp>

//********************************************************************************
// Singleton:
//********************************************************************************

std::unique_ptr<CoreManager> CoreManager::instance_(nullptr);

//--------------------------------------------------------------------------------

CoreManager::CoreManager() : listenPort_(0) {
}

//--------------------------------------------------------------------------------

CoreManager::~CoreManager() {
}

//--------------------------------------------------------------------------------

CoreManager * CoreManager::Instance() {
    if (!instance_) {
        instance_.reset(new CoreManager());
    }
    return instance_.get();
}

//--------------------------------------------------------------------------------

CoreManager & CoreManager::Reference() {
    return *Instance();
}

//********************************************************************************
// Properties:
//********************************************************************************

void CoreManager::SetListenPort(uint16_t value) {
    listenPort_ = value;
}

//********************************************************************************
// Methods:
//********************************************************************************

void CoreManager::Initialize() {
    listenPort_ = static_cast<uint16_t>(std::stoi(Options::Get(Options::PORT_NUMBER_KEY)));
    //...
}
