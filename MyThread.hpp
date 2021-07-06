#ifndef _MYTHREAD_
#define _MYTHREAD_

#include <mutex>

class MyThread
{
    public:
        MyThread();
        ~MyThread();
        static std::mutex m;
        void run(unsigned threadCount);
        void printout();

    private:
        int i_;
};


#endif