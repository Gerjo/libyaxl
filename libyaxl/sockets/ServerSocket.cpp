#include "ServerSocket.h"
#include "Socket.h"

namespace yaxl {
    namespace socket {

        ServerSocket::ServerSocket(int port, int backlog) :
        yes(1), no(0),
        _port(port),
        _backlog(backlog),
        _socketFd(0)
        {
            setup();
        }

        ServerSocket::ServerSocket(const ServerSocket& orig) :  yes(1), no(0) {

        }

        ServerSocket::~ServerSocket() {

        }

        void ServerSocket::setReuseAddress(bool newState) {
            const int& newFlag = newState ? yes : no;

            if(::setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, (void*) &newFlag, sizeof(newFlag)) < 0) {
                throw SocketException(strerror(errno));
            }
        }

        void ServerSocket::setKeepAlive(bool newState) {
            const int& newFlag = newState ? yes : no;

            if(::setsockopt(_socketFd, SOL_SOCKET, SO_KEEPALIVE, (void*) &newFlag, sizeof(newFlag)) < 0) {
                throw SocketException(strerror(errno));
            }
        }

        void ServerSocket::setup() {
            if(_socketFd != 0) {
                throw SocketException("ServerSocket is already listening.");
            }

            Socket::setupWGA();

            _socketFd = ::socket(AF_INET, SOCK_STREAM, 0);

            if (_socketFd < 0) {
                throw SocketException(strerror(errno));
            }

            sockaddr_in serv_addr;
            serv_addr.sin_family        = AF_INET;
            serv_addr.sin_addr.s_addr   = INADDR_ANY; // TODO: variable.
            serv_addr.sin_port          = htons(_port);

            if (::bind(_socketFd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                throw SocketException(strerror(errno));
            }

            if (::listen(_socketFd, _backlog) < 0) {
                throw SocketException(strerror(errno));
            }
        }

        Socket* ServerSocket::accept(void) {
            sockaddr_in cli_addr;
            socklen_t clilen = sizeof(cli_addr);

            int newsockfd   = ::accept(_socketFd, (sockaddr*) &cli_addr, &clilen);

            if(newsockfd <= 0) {
                throw SocketException(strerror(errno));
            }

            Socket* sock = new Socket(newsockfd);

            return sock;
        }
    }
}