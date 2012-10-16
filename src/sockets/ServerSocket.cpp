#include "ServerSocket.h"

namespace yaxl {
    namespace socket {

        ServerSocket::ServerSocket(int port) : _port(port) {
            _socketFd = 0;
            setup();
        }

        ServerSocket::ServerSocket(const ServerSocket& orig) {

        }

        ServerSocket::~ServerSocket() {

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


            char yes = 1;
            char no  = 1;

            if((::setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) || // prevents the "port in use" err.
                (::setsockopt(_socketFd, SOL_SOCKET, SO_KEEPALIVE, &no, sizeof(int)) == -1 )){

                throw SocketException(strerror(errno));
            }

            sockaddr_in serv_addr;
            serv_addr.sin_family        = AF_INET;
            serv_addr.sin_addr.s_addr   = INADDR_ANY; // TODO: variable.
            serv_addr.sin_port          = htons(_port);

            if (::bind(_socketFd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                throw SocketException(strerror(errno));
            }

            if (::listen(_socketFd, 10) < 0) {
                throw SocketException(strerror(errno));
            }
        }

        Socket* ServerSocket::accept(void) {
            sockaddr_in cli_addr;
            socklen_t clilen = sizeof(cli_addr);

            int newsockfd   = ::accept(_socketFd, (sockaddr *) &cli_addr, &clilen);

            if(newsockfd <= 0) {
                throw SocketException(strerror(errno));
            }

            Socket* sock = new Socket(newsockfd);

            return sock;
        }
    }
}