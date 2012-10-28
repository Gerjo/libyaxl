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
                // NB: if you are getting a "called without active exception"
                // and you are performing a delete call on a Thread instance
                // then you must *probably* call detatch() on this thread first.

                // More cryptic: Only the thread that spawned a thread can stop
                // that thread, onless this thread is detached, or joined and both
                // threads run out of scope. -- Gerjo
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
            } else {
                throw ConcurrencyException("Cannot join a not running thread.");
            }
        }

        void Thread::run() {
            if(_runnable != 0) {
                _runnable->run();
            } else {
                // The user probably extends Thread, and is calling the
                // super class' run() method. That's OK.
            }
        }

        void Thread::detach() {
            if(_thread != 0) {
                _thread->detach();
            } else {
                throw ConcurrencyException("Cannot detach a not running thread.");
            }
        }

        bool Thread::joinable() {
            if(_thread != 0) {
                return _thread->joinable();
            } else {
                return false;
            }
        }

        // Protected method.
        void Thread::sleep(long milliseconds) {
            std::chrono::milliseconds duration(milliseconds);
            std::this_thread::sleep_for(duration);
        }
    }
}