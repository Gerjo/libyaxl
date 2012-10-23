#include "Thread.h"

namespace yaxl {
    namespace concurrency {

        Thread::Thread() {
            _thread   = 0;
            _runnable = 0;
        }

        Thread::Thread(Runnable* runnable) {
            _thread   = 0;
            _runnable = runnable;
        }

        Thread::Thread(const Thread& orig) {

        }

        Thread::~Thread() {
            if(_thread != 0) {
                delete _thread;
            }
        }

        void Thread::start() {
            if(_thread == 0) {
                _thread = new std::thread(
                    [this] () {
                        run();
                    }
                );
            } else {
                throw ConcurrencyException("Thread is already started.");
            }
        }

        void Thread::join() {
            if(_thread != 0) {
                _thread->join();
            }
        }

        void Thread::run() {
            if(_runnable != 0) {
                _runnable->run();
            }
        }
    }
}