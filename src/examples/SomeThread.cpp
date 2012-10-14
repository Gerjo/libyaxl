#include "SomeThread.h"

SomeThread::SomeThread() {

}

void SomeThread::run() {
    for(int i = 1, max = 10; i <= max; ++i) {
        std::cout << "SomeThread count: " << i << "/" << max << endl;
    }
}
