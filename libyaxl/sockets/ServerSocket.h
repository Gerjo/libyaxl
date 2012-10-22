#ifndef SERVERSOCKET_H
#define	SERVERSOCKET_H

#include "SocketException.h"
#include "Socket.h"
#include "../common/CompileConfig.h"

namespace yaxl {
    namespace socket {

        class LIBEXPORT ServerSocket {
        public:
            ServerSocket(int port, int backlog = 10);
            virtual ~ServerSocket();

            Socket* accept(void);
            void setReuseAddress(bool newState);
            void setKeepAlive(bool newState);

        private:
            const int yes = 1;
            const int no  = 0;

            ServerSocket(const ServerSocket& orig);
            int _socketFd;
            int _port;
            int _backlog;
            void setup();
        };


    }
}


#endif	/* SERVERSOCKET_H */

