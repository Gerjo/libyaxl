#ifndef THREAD_H
#define	THREAD_H

#include <iostream>
#include <string>
#include <thread>

#include "Runnable.h"
#include "ConcurrencyException.h"
#include "../common/CompileConfig.h"

using namespace std;

namespace yaxl {
    namespace concurrency {
        class LIBEXPORT Thread : public Runnable {
        public:
            Thread();
            Thread(Runnable* runnable);
            virtual ~Thread();
            virtual void run();
            void operator()();
            void start();
            void join();

        private:
            Thread(const Thread& orig);
            std::thread* _thread;
            Runnable* _runnable;
        };

    }
}

#endif	/* THREAD_H */

