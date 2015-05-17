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

#ifndef __MEDUSA_TASK_CONNECTION__
#define __MEDUSA_TASK_CONNECTION__

#include <Connection.hpp>

class JobDescriptor;

//********************************************************************************
// TaskConnection:
//********************************************************************************

class TaskConnection : public Connection {
protected:
    // Fields:
    JobDescriptor * descriptor_;
    // Methods:
    void process(int8_t * buffer, size_t length);
public:
    // Constructors:
    TaskConnection(SharedSocket & socket);
    virtual ~TaskConnection();
    // Methods:
    virtual void Run();
};

#endif
