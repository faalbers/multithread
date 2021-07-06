#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>

// Using a function
void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "f1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// Using a funtion passing a reference
void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "f2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// Using a class object and runing the object method bar 
class Foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Foo::bar executing\n";

            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    int n = 0;
};

// Using a Functor
class baz
{
public:
    void operator()()
    {
        std::cout << "baz n: " << n << "\n";
        for (int i = 0; i < 5; ++i) {
            std::cout << "baz::operator() executing\n";
            ++n;
            std::cout << "blah: " << n << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 3;
};
 
int main()
{
    int n = 0;
    Foo f;
    baz b;

    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    std::thread t5(&Foo::bar, &f); // t5 runs foo::bar() on object f
    std::thread t6(b); // t6 runs baz::operator() on a copy of object b . Functor
    if ( t1.joinable() ) t1.join();
    if ( t2.joinable() ) t2.join();
    if ( t3.joinable() ) t3.join();
    if ( t4.joinable() ) t4.join();
    if ( t5.joinable() ) t5.join();
    if ( t6.joinable() ) t6.join();

    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
    std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';
}