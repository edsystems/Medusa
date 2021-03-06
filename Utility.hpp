//********************************************************************************
// Medusa, a distributed embedded system to apply filters on image files.
// Copyright (C) 2015  Gorka Su�rez Garc�a, Dan Cristian Rotaru
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

#ifndef __MEDUSA_UTILITY__
#define __MEDUSA_UTILITY__

#include <string>
#include <cstdint>

void LogWriteLine(const std::string & line);
bool IsPortNumber(const std::string & victim);
void InitializeRandom();
int GetRandom(int max);
int GetRandom();
uint32_t BigToLittleEndian(uint32_t victim);
std::string GetPathExtension(const std::string & path);

#endif
