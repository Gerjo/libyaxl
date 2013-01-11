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

        InputStream::InputStream(Socket& socket) : socket(socket), _isBlocking(false), _isStopping(false) {

        }

        InputStream::InputStream(const InputStream& orig) : socket(orig.socket) {

        }

        InputStream::~InputStream(void) {
            forceQuit();
        }

        void InputStream::concatToBuffer(char* otherBuffer, const int len) {
            for (int i = 0; i < len; ++i) {
                buffer.push_back(otherBuffer[i]);
            }
        }

        bool InputStream::ensureAvailable(size_t byteCount) {
            // We're not advocating busy waiting loops. If you must, then you can
            // implement your own!
            if(!_isBlocking) {
                throw SocketException("Please enable blocking sockets for your 'unsureAvailable' call to work.");
            }

            // Initial check, in case there is something left in the buffer, (this can
            // be nonblocking).
            size_t bytesAvailable = buffer.size();

            //cout << "[" << time(NULL) << "] Starting ensure while loop, available: " << bytesAvailable << " of " << byteCount << "byte(s)" << endl;

            while(bytesAvailable < byteCount && !_isStopping) {
                //cout << "[" << time(NULL) << "] blocking call placed, available:" << bytesAvailable << " of " << byteCount << endl;
                // The available call will be blocking.
                bytesAvailable = available();
            }

            // The data isn't actually "ensured", since we're exiting the application.
            if(_isStopping) {
                return false;
            }

            //cout << "[" << time(NULL) << "] Ensure read completed, available:" << bytesAvailable << " of " << byteCount << "byte(s)" << endl;

            // Semantic return statement :) Let the program continue.
            return true;
        }

        void InputStream::forceQuit(void) {
            _isStopping = true;
        }

        size_t InputStream::available(void) {
            const int socketFd = socket.getSocketFd();


            // Using select for time being. Will research non-blocking IO in
            // due time. -- Gerjo
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(socketFd, &fds);

            int r = -1;

            // Sorry about this :( time constraints and stuff.
            if(_isBlocking) {
                // OK, this is a bummer situation. The timeout is required, else it will
                // keep on blocking forever.
                //cout << "[" << time(NULL) << "] Running select. Two second delay. " << endl;
                timeval timeout = {2, 0};
                r = ::select(FD_SETSIZE, &fds, 0, 0, &timeout);

            } else {
                timeval timeout = {0, 0};
                r = ::select(FD_SETSIZE, &fds, 0, 0, &timeout);

            }

            if (r == -1) {
                throw SocketException(strerror(errno));
            }

            // Don't bother with anything.
            if(_isStopping) {
                return 0;
            }

            if(r == 0 && _isBlocking) {
                // symptom indicating the server may be offline.
                //throw SocketException("The server is offline or a SELECT() timeout was reached.");
            }

            if (FD_ISSET(socketFd, &fds)) {
                const int readChunkSize = 1024;
                char buff2[readChunkSize];
                int bytesRead;

                do {
                    bytesRead = ::recv(socketFd, reinterpret_cast<char*> (&buff2), readChunkSize, 0);

                    // We can read no more data at this time.
                    if (bytesRead == 0) {
                        // Possibly check against errno == 0? This may be a genuine error.
                        throw DisconnectedException();
                    }

                    if (bytesRead == -1) {
                        throw SocketException(strerror(errno));
                    }

                    concatToBuffer(buff2, bytesRead);

                } while (bytesRead > readChunkSize);

                return buffer.size();
            }

            return buffer.size();
        }

        string InputStream::read(const int numBytes) {
            const size_t limit = calculateReadLimit(numBytes);

            stringstream str;

            for (size_t i = 0; i < limit; ++i) {
                str << shiftBuffer();
            }

            return str.str();
        }

        char InputStream::read(void) {
            const size_t limit = calculateReadLimit(1);

            if (limit > 0) {
                return shiftBuffer();
            }

            // All empty, nothing to return. Java would return NULL here,
            // but C++ cannot. Possibly will throw an exception here.
            return '\0';
        }

        void InputStream::skip(const int skipBytes) {
            const size_t limit = calculateReadLimit(skipBytes);

            // Dispose the characters from the buffer.
            for (size_t i = 0; i < limit; ++i) {
                buffer.pop_front();
            }
        }

        inline size_t InputStream::calculateReadLimit(const size_t requestSize) {
            size_t bufferSize = buffer.size();

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

        void InputStream::setBlocking(bool isBlocking) {
            _isBlocking = isBlocking;
        }
    }
}