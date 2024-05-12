#include <iostream>
#include "thread"
#include <mutex>
#include "chrono"
#include <queue>
#include <condition_variable>
#include <list>

using namespace std;

//task 1
//int main() {
//    thread thr([] (int x) {cout << x * x << endl;}, 2);
//    thr.join();
//    thread thr1([] (int x) {cout << x * x << endl;}, 5);
//    thr1.join();
//    thread thr2([] (int x) {cout << x * x << endl;}, 10);
//    thr2.join();
//    return 0;
//}






//task 2
//int counter = 0;
//
//void threadFunction(int thread_id) {
//    for (int i = 0; i < 4; ++i) {
//        counter += thread_id;
//        cout << "Thread " << thread_id << ": counter = " << counter << endl;
//    }
//}
//
//int main() {
//    thread thread1(&threadFunction, 1);
//    thread thread2(&threadFunction, 2);
//
//    thread1.join();
//    thread2.join();
//
//    return 0;
//}






//task 3
//using namespace std;
//
//int counter = 0;
//mutex mtx;
//
//void threadFunction(int thread_id) {
//    for (int i = 0; i < 4; ++i) {
//        mtx.lock();
//        counter += thread_id;
//        cout << "Thread " << thread_id << ": counter = " << counter << endl;
//        mtx.unlock();
//    }
//}
//
//int main() {
//    thread thread1(&threadFunction, 1);
//    thread thread2(&threadFunction, 2);
//
//    thread1.join();
//    thread1.get_id();
//    thread2.join();
//
//
//    return 0;
//}







//task 4
//mutex mut2,mut1;
//void funcB() {
//    cout << "Thread2::Trying to lock mut2: " << endl;
//    lock_guard<mutex> lockGuard2(mut2);
//    cout << "Thread2::Mut2 was locked " << endl;
//    this_thread::sleep_for(10ms);
//    cout << "Thread2::Trying to lock mut1: " << endl;
//    lock_guard<std::mutex> lockGuard1(mut1);
//    cout << "Thread2::Mut1 was locked " << endl;
//    this_thread::sleep_for(100ms);
//    cout <<"Thread2::Thread 2 releases locks" << endl;
//}
//int main(){
//    thread thread1(funcB);
//
//    thread1.join();
//    return 0;
//}
//
//void funcA() {
//    cout << "Thread1::Trying to lock mut1 & mut2: " << endl;
//    scoped_lock scopedLock(mut1, mut2);
//    this_thread::sleep_for(100ms);
//    cout <<"Thread1::Thread 1 releases locks" << endl;
//}
//void funcB() {
//    cout << "Thread2::Trying to lock mut2 & mut1: " << endl;
//    scoped_lock scopedLock(mut2, mut1);
//    this_thread::sleep_for(100ms);
//    cout <<"Thread2::Thread 2 releases locks" << endl;
//}
//
//
//int main() {
//    thread thread1 (funcA);
//    thread1.join();
//    thread thread2(funcB);
//    thread2.join();
//}







template<typename T>
class Queue {

    int size;
    int max_size;
    list <T> thelist;

public:
    Queue(T data, int new_max_size) {
        list<T> temp(data);
        thelist = temp;
        size = 1;
        max_size = new_max_size;
    }
    void enqueue(T data) {
        if (!this->isFull()) {
            thelist.push_back(data);
            size++;
        } else {
            throw overflow_error("Queue is full.");
        }
    }
    T dequeue() {
        if (!this->isEmpty()) {
            T data = thelist.front();
            thelist.pop_back();
            --size;
            return data;
        } else {
            throw out_of_range("Queue is empty!");
        }
    }

    bool isEmpty() {
        if (size == 0) {
            return true;
        }
        return false;
    }
    bool isFull() {
        if (size == max_size) {
            return true;
        }
        return false;
    }
    int getMaxSize() {
        return max_size;
    }
};

mutex mute;
condition_variable cond_var;
bool flag = false;

Queue sharedData(1, 10);
 int deleted = sharedData.dequeue();

void Producer() {
    {
        lock_guard<mutex> guard_lock(mute);
        cout << "Mutex was locked for writing data." << endl;
        for (int i = 0; i < sharedData.getMaxSize(); i++) {
            sharedData.enqueue(5);
        }
        flag = true;
    }
    cond_var.notify_one();
}
void Consumer() {
    unique_lock<mutex> uniqueLock(mute);
    cout << "Mutex was locked for reading data." << endl;
    cond_var.wait(uniqueLock, []{return flag;});
    for (int i = 0; i < sharedData.getMaxSize(); i++) {
        cout << sharedData.dequeue() << " ";
    }
    cout << endl;
    cout << "Data was read." << endl;
}
void task5() {
    thread pr(Producer);
    thread cons(Consumer);

    pr.join();
    cons.join();
}

int main() {
    task5();

    return 0;
}






