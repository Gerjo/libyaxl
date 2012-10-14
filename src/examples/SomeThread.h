#ifndef SOMETHREAD_H
#define	SOMETHREAD_H

#include <iostream>

#include "../yaxl.h"

using namespace yaxl;
using namespace concurrency;


class SomeThread : public Thread {
public:
    SomeThread() {

    }
    
    void run() {
        for(int i = 1, max = 10; i <= max; ++i) {
            std::cout << "SomeThread count: " << i << "/" << max << endl;
        }
    }

private:

};

#endif	/* SOMETHREAD_H */

