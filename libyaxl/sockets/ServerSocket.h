#ifndef SERVERSOCKET_H
#define	SERVERSOCKET_H

#include "SocketException.h"
#include "Socket.h"

namespace yaxl {
    namespace socket {

        class ServerSocket {
        public:
            ServerSocket(int port);
            virtual ~ServerSocket();

            // TODO:
            Socket* accept(void);
            //void listen();

        private:
            ServerSocket(const ServerSocket& orig);
            int _socketFd;
            int _port;
            void setup();
        };


    }
}


#endif	/* SERVERSOCKET_H */

