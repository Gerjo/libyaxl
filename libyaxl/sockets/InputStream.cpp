/*
 * File:   InputStream.cpp
 * Author: gerjo
 *
 * Created on September 17, 2012, 6:50 PM
 */
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#endif

#include <vector>

#include "InputStream.h"
#include "Socket.h"

namespace yaxl {
    namespace socket {

        InputStream::InputStream(Socket& socket) : socket(socket) {

        }

        InputStream::InputStream(const InputStream& orig) : socket(orig.socket) {

        }

        void InputStream::concatToBuffer(char* otherBuffer, const int len) {
            for (int i = 0; i < len; ++i) {
                buffer.push_back(otherBuffer[i]);
            }
        }

        int InputStream::available(void) {
            const int socketFd = socket.getSocketFd();

            // Using select for time being. Will research non-blocking IO in
            // due time. -- Gerjo
            timeval timeout = {0, 0};
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(socketFd, &fds);

            if (select(FD_SETSIZE, &fds, 0, 0, &timeout) == -1) {
                throw SocketException(strerror(errno));
            }

            if (FD_ISSET(socketFd, &fds)) {
                const int readChunkSize = 1024;
                char buff2[readChunkSize];
                int bytesRead;

                do {
                    bytesRead = ::recv(socketFd, reinterpret_cast<char*> (&buff2), readChunkSize, 0);

                    // We can read no more data at this time.
                    if (bytesRead == 0) {
                        return buffer.size();
                    }

                    if (bytesRead == -1) {
                        throw SocketException(strerror(errno));
                    }

                    concatToBuffer(buff2, bytesRead);

                } while (bytesRead >= readChunkSize);

                return buffer.size();
            }

            return buffer.size();
        }

        string InputStream::read(const int numBytes) {
            const int limit = calculateReadLimit(numBytes);

            stringstream str;

            for (int i = 0; i < limit; ++i) {
                str << shiftBuffer();
            }

            return str.str();
        }
        
        char InputStream::read(void) {
            const int limit = calculateReadLimit(1);

            if (limit > 0) {
                return shiftBuffer();
            }

            // All empty, nothing to return. Java would return NULL here,
            // but C++ cannot. Possibly will throw an exception here.
            return '\0';
        }

        void InputStream::skip(const int skipBytes) {
            const int limit = calculateReadLimit(skipBytes);

            // Dispose the characters from the buffer.
            for (int i = 0; i < limit; ++i) {
                buffer.pop_front();
            }
        }

        const inline int InputStream::calculateReadLimit(const int requestSize) {
            int bufferSize = buffer.size();

            if (bufferSize < requestSize) {
                bufferSize = this->available();
            }

            return min(bufferSize, requestSize);
        }

        char inline InputStream::shiftBuffer(void) {
            char tmp = buffer.front();
            buffer.pop_front();
            return tmp;
        }
    }
}