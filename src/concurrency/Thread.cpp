#include "Thread.h"

namespace yaxl {
    namespace concurrency {

        Thread::Thread() {
            _thread = 0;
            cout << " done !" << endl;

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
                _thread = new std::thread(std::ref(*this));
            }
        }

        void Thread::join() {
            if(_thread != 0) {
                _thread->join();
            }
        }

        void Thread::operator()() {
            cout << "operator()()" << endl;
            run();
        }

        void Thread::run() {
            cout << "ran" << endl;
        }

    }
}