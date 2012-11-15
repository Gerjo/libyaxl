#ifndef DISCONNECTEXCEPTION_H
#define	DISCONNECTEXCEPTION_H

#include "SocketException.h"

namespace yaxl {
    namespace socket {

        class DisconnectedException : public SocketException {
        public:
            DisconnectedException() : SocketException(
                    "Socket was disconnected. You can no longer "
                    "assume reads or writes to this socket will work.") {
            }
        };
    }
}

#endif	/* DISCONNECTEXCEPTION_H */

