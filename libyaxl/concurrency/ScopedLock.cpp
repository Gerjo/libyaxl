#include "ScopedLock.h"

namespace yaxl {
    namespace concurrency {
        ScopedLock::ScopedLock(Mutex& mutex) : _mutex(mutex) {
            _mutex.lock();
        }

        ScopedLock::ScopedLock(Mutex* mutex) : _mutex(*mutex) {
            _mutex.lock();
        }

        ScopedLock::~ScopedLock() {
            _mutex.unlock();
        }
    }
}
