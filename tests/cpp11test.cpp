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
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>

void Cpp11Test() {
    std::vector<std::string> data { "Zeus", "Athenea", "Ares", "Apollo", "Aphrodite" };
    std::vector<std::thread> threads;
    std::mutex printMutex;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::for_each(
        std::begin(data), std::end(data),
        [&] (const std::string & victim) {
            threads.push_back(std::thread(
                [&] (const std::string & name) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 100));
                    printMutex.lock();
                    std::cout << "Hello, " << name << "." << std::endl;
                    printMutex.unlock();
                },
                victim
            ));
        }
    );
    std::for_each(
        std::begin(threads), std::end(threads),
        [] (std::thread & victim) {
            victim.join();
        }
    );
}
