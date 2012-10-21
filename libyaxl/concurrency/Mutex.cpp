#include "Mutex.h"

namespace yaxl {
    namespace concurrency {
        void Mutex::lock(void) {
            _mutex.lock();
        }

        void Mutex::unlock(void) {
            _mutex.unlock();
        }

        bool Mutex::tryLock(void) {
            return _mutex.try_lock();
        }
    }
}