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

#include <iostream>
#include <CoreManager.hpp>
#include <Options.hpp>
#include <Utility.hpp>

int main(int argc, char ** argv) {
    Options::Parse(argc, argv);
    if (Options::Get(Options::HelpKey) == Options::HELP_YES) {
        std::cout << "medusa [options]" << std::endl;
        std::cout << "\t--port   port => Changes the port of" << std::endl;
        std::cout << "\t -p      port    the server." << std::endl;
        std::cout << "\t--config path => The file to load with" << std::endl;
        std::cout << "\t -c      path    the configuration." << std::endl;
    } else {
        InitializeRandom();
        CoreManager::Instance()->Run();
    }
    return 0;
}
