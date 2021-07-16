
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include "Timer.hpp"

std::mutex mcout;

class MyThread {
    public:
        //MyThread() {
        //    //std::cout << "create MyThread\n";
        //}

        MyThread(int i) {
            i_ = i;
            //std::cout << "create MyThread\n";
        }
        
        ~MyThread() {
            //std::cout << "delete " << i_ << "\n";
        }
        
        void run()
        {
            //mcout.lock();
            //std::cout << "Start " << i_ << "\n";
            //mcout.unlock();
            double result;
            double test = 1234;
            for ( int i = 0; i < 1; i++) {
                for ( double j = 0; j < 100; j++) {
                    for ( double k = 0; k < 5000000; k++) {
                        result = (j * k * i) / test;
                    }
                }
            }
            //mcout.lock();
            //std::cout << "Stop " << i_ << "\n";
            //mcout.unlock();
        }

    private:
        int i_;
};

int main()
{
    std::vector<std::thread*> threads;

    {
        Timer tr("Threads Run");
        for (int i = 0; i < 64; i++) {
            std::shared_ptr<MyThread> mt(new MyThread(i));
            threads.push_back(new std::thread(&MyThread::run, mt));
        }
        for (std::thread *th : threads ) th->join();
    }

    return 0;
}
