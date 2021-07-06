#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mutty;

void myFunc(double i)
{
    double result;
    double test = 1234;
    for ( double j = 0; j < 5000000; j++) {
        for ( double k = 0; k < 1000; k++) {
            result = (i * j * k) / test;
        }
    }
    std::cout << result << std::endl;
}

class MyThread {
public:
    MyThread() { std::cout << "create MyThread\n"; }
    ~MyThread() { std::cout << "delete MyThread\n"; }
	void operator()(double i,double q) { fluff(i, q); }

    void fluff(double i, double q)
    {
        double result;
        double test = 1234;
        for ( double j = 0; j < 5000000; j++) {
            for ( double k = 0; k < 100; k++) {
                result = (1.0 * j * k) / test;
            }
        }
        mutty.lock();
	    std::cout << i << " " << q << std::endl;
        mutty.unlock();
    }
};

int main()
{
    std::vector<std::thread*> myThreads;

    for ( int i = 0; i < 8; i++) myThreads.push_back(new std::thread(MyThread(), i, i+1));

    for (std::thread *delthread : myThreads) delthread->join();

    for (std::thread *delthread : myThreads) delete delthread;

    /*
    std::thread t0(myFunc, 0);
    std::thread t1(myFunc, 1);
    std::thread t2(myFunc, 2);
    std::thread t3(myFunc, 3);
    std::thread t4(myFunc, 4);
    std::thread t5(myFunc, 5);
    std::thread t6(myFunc, 6);
    std::thread t7(myFunc, 7);

    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    */

    std::cout << "End\n";

}
