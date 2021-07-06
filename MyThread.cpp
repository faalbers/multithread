#include "MyThread.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex MyThread::m;

MyThread::MyThread()
    : i_(-1)
{
    m.lock();
    std::cout << "MyThread created \n";
    m.unlock();
}

MyThread::~MyThread()
{
    m.lock();
    std::cout << "MyThread deleted for thread " << i_ << "\n";
    m.unlock();
}

void MyThread::run(unsigned threadCount)
{
    i_ = threadCount;
    printout();
}

void MyThread::printout()
{
    m.lock();
    std::cout << "start   thread " << i_ << std::endl;
    m.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    m.lock();
    std::cout << "finnish thread " << i_ << std::endl;
    m.unlock();
}
