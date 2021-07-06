
#include "MyThread.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int main()
{
    unsigned coreCount = std::thread::hardware_concurrency();
    unsigned i;
    std::vector<std::thread*> threads;

    auto start = std::chrono::high_resolution_clock::now();

    MyThread mt;
    
    for ( i = 0; i < coreCount; i++ ) {
        // crerates a copy of mt and when the thread is done it deletes that copy
        threads.push_back(new std::thread(&MyThread::run, mt, i));

        MyThread::m.lock();
        std::cout << "created thread " << i << std::endl;
        MyThread::m.unlock();
    }

    MyThread::m.lock();
    std::cout << "start joining\n";
    MyThread::m.unlock();

    i = 0;
    for (std::thread *thread : threads ) {
        thread->join();
        
        MyThread::m.lock();
        std::cout << "joined thread " << i << std::endl;
        MyThread::m.unlock();
        i++;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    auto mills = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - start);

    std::cout << mills.count() << " ms\n";
    std::cout << "main done\n";

    return 0;
}