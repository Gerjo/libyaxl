#ifndef CONCURRENCYEXCEPTION_H
#define	CONCURRENCYEXCEPTION_H

#include "../common/YaxlException.h"

namespace yaxl {
    namespace concurrency {
        class ConcurrencyException : public YaxlException {
        public:
            ConcurrencyException(string error) : YaxlException(error) {

            }
        };
    }
}

#endif	/* CONCURRENCYEXCEPTION_H */

