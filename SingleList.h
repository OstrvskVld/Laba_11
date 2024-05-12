

#ifndef LABA_11_SINGLELIST_H
#define LABA_11_SINGLELIST_H


#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>


using namespace std;
class SafeList {
private:
    list<int> data;
    mutex mtx;
    condition_variable cv_producer;
    condition_variable cv_consumer;
    bool empty = true;

public:
    void enqueue(int item);
    int dequeue();
};


#endif //LABA_11_SINGLELIST_H
