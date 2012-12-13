#ifndef CONDITION_H_YAXL
#define	CONDITION_H_YAXL

#include <thread>
#include <mutex>
#include <condition_variable>

namespace yaxl {
    namespace concurrency {

        class Condition {
        public:
            void wait(long milliseconds) {
                std::unique_lock<std::mutex> lock(_mutex);

                _condition.wait_for(lock, std::chrono::milliseconds(milliseconds));
            }

            void wait() {
                std::unique_lock<std::mutex> lock(_mutex);

                _condition.wait(lock);
            }

            void signal() {
                std::unique_lock<std::mutex> lock(_mutex);
                _condition.notify_one();
            }
            
        private:
            Condition(const Condition&) {

            }

            std::mutex _mutex;
            std::condition_variable _condition;
        };
    }
}
#endif	/* CONDITION_H_YAXL */

