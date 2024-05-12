#include "SingleList.h"

void SafeList::enqueue(int item) {
    std::unique_lock<std::mutex> lock(mtx);
    while (!empty) {
        cv_producer.wait(lock);
    }

    data.push_back(item);
    empty = false;
    cv_consumer.notify_one();
}

int SafeList::dequeue() {
    std::unique_lock<std::mutex> lock(mtx);
    while (empty) {
        cv_consumer.wait(lock);
    }

    int item = data.front();
    data.pop_front();
    if (data.empty()) {
        empty = true;
        cv_producer.notify_one();
    }

    return item;
}
