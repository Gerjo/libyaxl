#ifndef SERVERSOCKET_H
#define	SERVERSOCKET_H

#include "SocketException.h"
#include "Socket.h"

namespace yaxl {
    namespace socket {

        class ServerSocket {
        public:
            ServerSocket();
            virtual ~ServerSocket();

            // TODO:
            Socket* accept(void);
            //void listen();


        private:
            ServerSocket(const ServerSocket& orig);
        };


    }
}


#endif	/* SERVERSOCKET_H */

