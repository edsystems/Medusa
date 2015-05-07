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

#ifndef __MEDUSA_OPTIONS__
#define __MEDUSA_OPTIONS__

#include <map>
#include <string>

class Options {
private:
    // Fields:
    static std::map<std::string, std::string> data_;
public:
    // Constants:
    static const std::string HELP_KEY;
    static const std::string HELP_NO;
    static const std::string HELP_YES;
    static const std::string PORT_NUMBER_KEY;
    static const std::string PORT_NUMBER_VAL;
    static const std::string CONFIG_FILE_KEY;
    static const std::string CONFIG_FILE_VAL;
    // Methods:
    static void Parse(int argc, char ** argv);
    static const std::string & Get(const std::string & key);
};

#endif
