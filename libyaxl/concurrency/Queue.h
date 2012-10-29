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
                yaxl::concurrency::ScopedLock meh(_mutex);

                if(_storage.empty()) {
                    return 0;
                }

                T* item = _storage.front();

                // Hopefully due to a "scoped" lock, this won't yield
                // deadlocks. TODO: reseach that.
                _storage.pop_front();

                return item;
            }

            void push(T* item) {
                yaxl::concurrency::ScopedLock meh(_mutex);
                _storage.push_back(item);
            }

        private:
            deque<T*> _storage;
            Mutex _mutex;
        };

    }
}
#endif	/* QUEUE_H */

