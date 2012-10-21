#ifndef MUTEX_H
#define	MUTEX_H

#include "../common/CompileConfig.h"
#include <mutex>

namespace yaxl {
    namespace concurrency {
        class LIBEXPORT Mutex {
        public:
            void lock(void);
            void unlock(void);
            bool tryLock(void);

        private:
            std::mutex _mutex;
        };

    }
}

#endif	/* MUTEX_H */

