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

#include "Options.hpp"

#include <iostream>
#include <exception>
#include <Utility.hpp>

//********************************************************************************
// [Options] Constants:
//********************************************************************************

const std::string Options::HELP_NO("no");
const std::string Options::HELP_YES("yes");
const std::string Options::PORT_NUMBER_VAL("3074");
const std::string Options::SERVERS_FILE_VAL("servers.csv");

//********************************************************************************
// [Options] Fields:
//********************************************************************************

std::map<Options::Key, std::string> Options::data_;

//********************************************************************************
// [Options] Methods:
//********************************************************************************

void Options::Parse(int argc, char ** argv) {
    // Initialization of the options data:
    data_.clear();
    data_[HelpKey] = HELP_NO;
    data_[PortNumberKey] = PORT_NUMBER_VAL;
    data_[ServersFileKey] = SERVERS_FILE_VAL;
    // Parse the command arguments:
    for (int i = 0; i < argc; ++i) {
        std::string item(argv[i]);
        if (item == "-p" || item == "--port") {
            // Check the port option:
            ++i;
            if (i < argc) {
                std::string value(argv[i]);
                if (IsPortNumber(value)) {
                    data_[PortNumberKey] = value;
                }
            }
        } else if (item == "-s" || item == "--servers") {
            // Check the servers file option:
            ++i;
            if (i < argc) {
                std::string value(argv[i]);
                data_[ServersFileKey] = value;
            }
        } else if (item == "-h" || item == "--help") {
            // Check the help option:
            data_[HelpKey] = HELP_YES;
        }
    }
}

//--------------------------------------------------------------------------------

const std::string & Options::Get(Key key) {
    if (data_.count(key)) {
        return data_[key];
    } else {
        throw std::exception("[Options::Get] Invalid key!");
    }
}
