/*
 * File:   OutputStream.cpp
 * Author: gerjo
 *
 * Created on September 17, 2012, 6:30 PM
 */
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
	#include <winsock2.h>
	#include <windows.h>
#endif

#include "OutputStream.h"
#include "SocketException.h"
#include "Socket.h"

namespace yaxl {
    namespace socket {

        OutputStream::OutputStream(Socket& socket) : socket(socket) {

        }

        OutputStream::OutputStream(const OutputStream& orig) : socket(orig.socket) {

        }

        void OutputStream::write(const stringstream ssToSend) {
            write(ssToSend.str());
        }

        void OutputStream::write(const string stringToSend) {
            write(stringToSend.c_str(), stringToSend.length());
        }

        // Relies on strlen(), so very unsafe for anything but c style strings.
        void OutputStream::write(const char* bytes) {
            write(bytes, strlen(bytes));
        }

        void OutputStream::write(const char* bytes, const int sendLength) {
            const int socketFd = socket.getSocketFd();
            const char* start  = bytes;
            int bytesSent      = 0;
            int total          = 0;

            do {
                bytesSent = ::send(socketFd, (start + total), sendLength, MSG_NOSIGNAL);
                if (bytesSent == -1) {
                    if (errno == EINTR || errno == EAGAIN) {
                        continue;
                    }

                    throw SocketException(strerror(errno));
                    break;
                }

                if ((total += bytesSent) < sendLength) {
                    continue;
                }

                // We reached this point, so all data is sent.
                break;
            } while (true);
        }
    }
}
