
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <chrono>

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

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 64; i++) {
        std::shared_ptr<MyThread> mt(new MyThread(i));
        threads.push_back(new std::thread(&MyThread::run, mt));
    }
    for (std::thread *th : threads ) th->join();

    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";

    return 0;
}
