#ifndef THREAD_H
#define	THREAD_H

#include <iostream>
#include <string>
#include <thread>

#include "Runnable.h"

using namespace std;

namespace yaxl {
    namespace concurrency {
        class Thread : public Runnable {
        public:
            Thread();
            virtual ~Thread();
            virtual void run();

            void operator()();
            Thread(const Thread& orig);

            void start();
            void join();
        private:
            std::thread* _thread;
        };

    }
}

#endif	/* THREAD_H */

