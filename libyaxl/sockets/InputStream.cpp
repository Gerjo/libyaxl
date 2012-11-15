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

        bool InputStream::ensureAvailable(int byteCount) {
            // We're not advocating busy waiting loops. If you must, then you can
            // implement your own!
            if(!_isBlocking) {
                throw SocketException("Please enable blocking sockets for your 'unsureAvailable' call to work.");
            }

            // Initial check, in case there is something left in the buffer, (this can
            // be nonblocking).
            int bytesAvailable = buffer.size();

            while(bytesAvailable < byteCount && !_isStopping) {
                //cout << "blocking call placed. Available:" << bytesAvailable << ", desired:" << byteCount << endl;
                // The available call will be blocking.
                bytesAvailable = available();
            }

            // The data isn't actually "ensured", since we're exiting the application.
            if(_isStopping) {
                return false;
            }

            //cout << "Ensure read completed. Available:" << bytesAvailable << ", desired:" << byteCount << endl;

            // Semantic return statement :) Let the program continue.
            return true;
        }

        void InputStream::forceQuit(void) {
            _isStopping = true;
        }

        int InputStream::available(void) {
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

        void InputStream::setBlocking(bool isBlocking) {
            _isBlocking = isBlocking;
        }
    }
}