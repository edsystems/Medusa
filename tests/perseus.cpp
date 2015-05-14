//********************************************************************************
// Perseus, a simple client to use Medusa server.
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

#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <Options.hpp>
#include <Message.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main(int argc, char ** argv) {
    try {
        bool notExit = true;
        boost::array<int8_t, Message::MAX_SIZE> buffer;
        boost::system::error_code error;
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("localhost", Options::PORT_NUMBER_VAL);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        auto socketBuffer = boost::asio::buffer(buffer);
        boost::asio::connect(socket, endpoint_iterator);
        while (notExit) {
            Message::SendJobRequest(&socket, "png", 816614, 0);
            size_t length = socket.read_some(socketBuffer, error);
            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            } else {
                auto * bufferPtr = buffer.c_array();
                if (*bufferPtr == Message::JOB_ACCEPTED_ID && length == sizeof(Message::JobAccepted)) {
                    auto * msg = (Message::JobAccepted *)bufferPtr;
                    JobIdentifier identifier(msg->jobId);
                    cout << "Job accepted from " << socket.remote_endpoint().address() << endl;
                    cout << "-> Identifier: " << identifier.ToString() << endl;
                    socket.close();
                    notExit = false;
                } else if (*bufferPtr == Message::ERROR_RESPONSE_ID && length == sizeof(Message::ErrorResponse)) {
                    auto * msg = (Message::ErrorResponse *)bufferPtr;
                    cout << "Error from " << socket.remote_endpoint().address() << endl;
                    cout << "-> Code: " << msg->errorCode << endl;
                } else {
                    cout << "Unknown message!" << endl;
                }
            }
        }
    } catch (exception & e) {
        cerr << e.what() << endl;
    }
    return 0;
}
