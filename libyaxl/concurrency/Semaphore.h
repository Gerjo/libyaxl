#ifndef SEMAPHORE_H_YAXL
#define	SEMAPHORE_H_YAXL

#include <thread>
#include <mutex>
#include <condition_variable>

// NB: reference design: http://pastebin.com/bfPChHC0, which in turn is based
// on "The little book of semaphores".

// We may or may need to keep track of _wakeups, using just _count may
// be buggy. -- Gerjo

namespace yaxl {
    namespace concurrency {

        class Semaphore {
        public:

            Semaphore(int count = 0) : _count(count) {

            }

            void wait() {
                std::unique_lock<std::mutex> lock(_mutex);

                // As always, account for spurious wakeups.
                while (_count <= 0) {
                    _condition.wait(lock);
                }

                --_count;
            }

            void signal(int count = 1) {
                std::unique_lock<std::mutex> lock(_mutex);

                _count += count;

                for (; count > 0; --count) {
                    _condition.notify_one();
                }
            }

        private:
            int _count;
            std::mutex _mutex;
            std::condition_variable _condition;
        };
    }
}


#endif	/* SEMAPHORE_H_YAXL */

