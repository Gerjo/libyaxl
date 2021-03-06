#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <ws2tcpip.h>
#endif

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
            const char& newFlag = newState ? yes : no;

            if(::setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &newFlag, sizeof(int)) < 0) {
                throw SocketException(strerror(errno));
            }
        }

        void ServerSocket::setKeepAlive(bool newState) {
            const char& newFlag = newState ? yes : no;

            if(::setsockopt(_socketFd, SOL_SOCKET, SO_KEEPALIVE, &newFlag, sizeof(int)) < 0) {
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

            setReuseAddress(true);

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

            char ipv4[16];

            #ifdef _WIN32
                InetNtop(AF_INET, &(cli_addr.sin_addr), ipv4, sizeof(ipv4));
            #else
                inet_ntop(AF_INET, &(cli_addr.sin_addr), ipv4, sizeof(ipv4));
            #endif

            int port = ntohs(cli_addr.sin_port);

            Socket* sock = new Socket(newsockfd, ipv4, port);

            return sock;
        }
    }
}