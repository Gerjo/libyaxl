/*
 * File:   SocketException.h
 * Author: gerjo
 *
 * Created on September 18, 2012, 10:50 PM
 */

#ifndef SOCKETEXCEPTION_H
#define	SOCKETEXCEPTION_H

#include "../common/YaxlException.h"


namespace yaxl {
    namespace socket {
        class SocketException : public YaxlException {
        public:
            SocketException(string error) : YaxlException(error) {

            }
        };
    }
}

#endif	/* SOCKETEXCEPTION_H */

