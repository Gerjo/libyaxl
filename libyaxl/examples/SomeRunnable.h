#ifndef SOMERUNNABLE_H
#define	SOMERUNNABLE_H

#include "../concurrency/concurrency.h"
#include <iostream>

using namespace yaxl;
using namespace yaxl::concurrency;

class SomeRunnable : public Runnable {
    virtual void run() {
        for(int i = 1, max = 5; i <= max; ++i) {
            std::cout << "SomeRunnable count: " << i << "/" << max << endl;
        }
    }
};

#endif	/* SOMERUNNABLE_H */

