#ifndef DEQUE_H
#define	DEQUE_H

#include <deque>

#include "Mutex.h"

namespace yaxl {
    namespace concurrency {

        template <class T>
        class Stack {
        public:
            Stack() {

            }

            virtual ~Stack() {
                
            }

            T tryPop(void) {
                T item = 0;

                _mutex.lock();

                if (!_deque.empty()) {
                    item = _deque.back();
                    _deque.pop_back();
                }

                _mutex.unlock();
                return item;
            }

            void push(T item) {
                _mutex.lock();
                _deque.push_back(item);
                _mutex.unlock();
            }

        private:
            Stack(const Stack& orig);
            std::deque<T> _deque;
            Mutex _mutex;
        };
    }
}

#endif	/* DEQUE_H */

