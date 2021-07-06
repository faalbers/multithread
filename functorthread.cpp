#include <iostream>
#include <string>
#include <thread>
#include <mutex>

std::mutex m;

class MyFunctor
{
    int n_ = 5;
    std::string name_;

public:
    MyFunctor(std::string name) : name_(name) {}

    void operator()()
    {
        for (int i = 0; i < 5; ++i) ++n_;
        m.lock();
        std::cout << "Functor: " << name_ << ": " << n_ << std::endl;
        m.unlock();
    }

    std::string getN() { return (name_ + ": " + std::to_string(n_)); }
};

int main()
{
    MyFunctor mf1("Referenced"), mf2("Copied");

    std::thread t1(std::ref(mf1));  // run on reference of mf
    std::thread t2(mf2);            // run on copy mf
    t1.join();
    t2.join();

    std::cout << mf1.getN() << std::endl;
    std::cout << mf2.getN() << std::endl;

    return 0;
}
