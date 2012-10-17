#ifndef RUNNABLE_H
#define	RUNNABLE_H

#include "../common/CompileConfig.h"

namespace yaxl {
    namespace concurrency {
        class LIBEXPORT Runnable {
        public:
            virtual void run() = 0;
        };
    }
}

#endif	/* RUNNABLE_H */
