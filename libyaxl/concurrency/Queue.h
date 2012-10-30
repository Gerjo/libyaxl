#ifndef QUEUE_H
#define	QUEUE_H

#include "Mutex.h"
#include "ScopedLock.h"
#include <deque>

using std::deque;

namespace yaxl {
    namespace concurrency {

        template <class T>
        class LIBEXPORT Queue {
        public:
            Queue() {

            }

            virtual ~Queue() {

            }

            T* tryPop(void) {
                if(_storage.empty()) {
                    return 0;
                }
                //yaxl::concurrency::ScopedLock meh(_mutex);
                T* item = _storage.front();

                _storage.pop_front();

                return item;
            }

            void push(T* item) {
                //yaxl::concurrency::ScopedLock meh(_mutex);
                _storage.push_back(item);
            }

        private:
            deque<T*> _storage;
            Mutex _mutex;
        };

    }
}
#endif	/* QUEUE_H */

