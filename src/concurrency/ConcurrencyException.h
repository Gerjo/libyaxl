#ifndef CONCURRENCYEXCEPTION_H
#define	CONCURRENCYEXCEPTION_H

namespace yaxl {
    namespace file {
        class ConcurrencyException : public YaxlException {
        public:
            ConcurrencyException(string error) : YaxlException(error) {
                
            }
        };
    }
}

#endif	/* CONCURRENCYEXCEPTION_H */

