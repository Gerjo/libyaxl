#ifndef RUNNABLE_H
#define	RUNNABLE_H

namespace yaxl {
    namespace concurrency {
        class Runnable {
            virtual void run() = 0;
        };
    }
}

#endif	/* RUNNABLE_H */
