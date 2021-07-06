#include "MyThread.hpp"
#include <iostream>

int main()
{
    MyThread::m.lock();
    MyThread::m.unlock();
    return 0;
}