#ifndef SOMETHREAD_H
#define	SOMETHREAD_H

#include <iostream>

#include "../yaxl.h"

using namespace yaxl;
using namespace concurrency;


class SomeThread : public Thread {
public:
    SomeThread();
    virtual void run();
private:

};

#endif	/* SOMETHREAD_H */

