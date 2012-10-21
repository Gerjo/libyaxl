#ifndef LOCK_H
#define	LOCK_H

#include "Mutex.h"
#include "../common/CompileConfig.h"

namespace yaxl {
    namespace concurrency {
        class LIBEXPORT ScopedLock {
        public:
            ScopedLock(Mutex& mutex);
            ScopedLock(Mutex* mutex);
            ~ScopedLock();

        private:
            Mutex& _mutex;
        };
    }
}

#endif	/* LOCK_H */

