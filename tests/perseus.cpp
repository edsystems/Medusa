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
#include <Message.hpp>
#include <FragmentedFile.hpp>

using boost::asio::ip::tcp;
using namespace std;

template <typename TFunc>
bool ReceiveMessage(tcp::socket & socket, TFunc handler) {
    boost::system::error_code error;
    boost::array<int8_t, Message::MAX_SIZE> buffer;
    auto socketBuffer = boost::asio::buffer(buffer);
    size_t length = socket.read_some(socketBuffer, error);
    if (error == boost::asio::error::eof) {
        cerr << "ERROR: Connection closed!" << endl;
        return false;
    } else if (error) {
        throw boost::system::system_error(error);
    } else {
        handler(buffer.c_array(), length);
    }
    return true;
}

void OnProcessFlags(tcp::socket & socket, bool exitProcess, bool socketEof) {
    if (socketEof) {
        exit(0);
    } else if (exitProcess) {
        cerr << "WARNING: Unexpected behaviour!" << endl;
        cerr << "WARNING: Closing socket & exit the process" << endl;
        socket.close();
        exit(0);
    }
}

int main(int argc, char ** argv) {
    try {
        // Get the parameters:
        if (argc != 5) return 0;
        std::string serverAddress(argv[1]);
        std::string serverPort(argv[2]);
        std::string imagePath(argv[3]);
        int filterSelected = std::stoi(std::string(argv[4]));
        // Load the image file:
        FragmentedFile inputImageFile(Message::MAX_FRAGMENT_SIZE);
        if (!inputImageFile.Load(imagePath)) return 0;
        std::string imageExtension = inputImageFile.GetPathExtension();
        cout << "LOADED: " << inputImageFile.GetPath() << endl;
        cout << "+ File length:  " << inputImageFile.GetSize() << endl;
        cout << "+ Chunk length: " << inputImageFile.GetChunkSize() << endl;
        cout << "+ Chunks count: " << inputImageFile.GetNumberOfChunks() << endl;
        cout << "+ Extension:    " << imageExtension << endl;
        // Get the socket connected to the server:
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(serverAddress, serverPort);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        cout << "CONNECTED: " << serverAddress << " (" << serverPort << ")" << endl;
        cout << "+ Local:  " << socket.local_endpoint().address() << ":"
             << socket.local_endpoint().port() << endl;
        cout << "+ Remote: " << socket.remote_endpoint().address() << ":"
             << socket.remote_endpoint().port() << endl;
        // Send the job request:
        cout << "SEND: Job request" << endl;
        bool exitProcess = false;
        JobIdentifier::DigestArray jobId;
        Message::SendJobRequest(&socket, imageExtension, inputImageFile.GetSize(), filterSelected);
        bool socketEof = ReceiveMessage(socket, [&] (int8_t * buffer, size_t length) {
            if (*buffer == Message::JOB_ACCEPTED_ID && length == sizeof(Message::JobAccepted)) {
                auto * msg = (Message::JobAccepted *)buffer;
                memcpy(jobId, msg->jobId, sizeof(JobIdentifier::DigestArray));
                JobIdentifier identifier(msg->jobId);
                cout << "RECEIVED: Job accepted" << endl;
                cout << "+ Identifier: " << identifier.ToString() << endl;
            } else if (*buffer == Message::ERROR_RESPONSE_ID && length == sizeof(Message::ErrorResponse)) {
                auto * msg = (Message::ErrorResponse *)buffer;
                cout << "RECEIVED: Error response" << endl;
                cout << "+ Code: " << msg->errorCode << endl;
                exitProcess = true;
            } else {
                exitProcess = true;
            }
        });
        OnProcessFlags(socket, exitProcess, socketEof);
        socket.close();
    } catch (exception & e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    return 0;
}
