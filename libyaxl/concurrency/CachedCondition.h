#ifndef CACHEDCONDITION_H
#define	CACHEDCONDITION_H

#include <thread>
#include <mutex>
#include <condition_variable>

namespace yaxl {
    namespace concurrency {

        class CachedCondition {
        public:
            CachedCondition() : _isSignalled(false) {}

            void wait(long milliseconds) {
                std::unique_lock<std::mutex> lock(_mutex);

                if(_isSignalled) {
                    _isSignalled = false;
                    return;
                }

                _condition.wait_for(lock, std::chrono::milliseconds(milliseconds));
                _isSignalled = false;
            }

            void wait() {
                std::unique_lock<std::mutex> lock(_mutex);

                if(_isSignalled) {
                    _isSignalled = false;
                    return;
                }
                
                _condition.wait(lock);
                _isSignalled = false;
            }

            void signal() {
                std::unique_lock<std::mutex> lock(_mutex);
                _isSignalled = true;
                _condition.notify_one();
            }

        private:
            CachedCondition(const CachedCondition& orig) {

            }

            bool _isSignalled;

            std::mutex _mutex;
            std::condition_variable _condition;
        };

    }
}


#endif	/* CACHEDCONDITION_H */

