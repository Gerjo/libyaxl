#ifndef THREAD_H
#define	THREAD_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>

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
            virtual void start();
            void join();
            void detach();
            bool joinable();

        protected:
            void sleep(long milliseconds);

        private:
            Thread(const Thread& orig);
            std::thread* _thread;
            Runnable* _runnable;
        };

    }
}

#endif	/* THREAD_H */

