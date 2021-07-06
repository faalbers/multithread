#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

long balance = 0;
std::mutex m;
std::condition_variable cv;

void addMoney (int money)
{
    // as the mutex gets released, this will aquire itand add the money
    // lock_guard is a wrapper that will release the mutex once this
    // thread goes out of scope
    std::lock_guard<std::mutex> lg(m);
    balance += money;
    std::cout << "Amount added: " << money << std::endl;
    std::cout << "Current balance: " << balance << std::endl;
    // whatever thread is waiting for cv, notify it with only_one because
    // there is only one other thread
    cv.notify_one();
}

void redrawMoney(int money)
{
    // wrapper for m , own it and lock it
    std::unique_lock<std::mutex> ul(m);
    // pass unique lock to condition wait and add a oredicate condition
    // it waits till condition is true by releasing the mutex m
    // after cv gets notified it will try to lock m and try the condition again
    // it will wait again while is true and notified again
    cv.wait(ul, [] { return (balance != 0) ? true : false; }) ;
    if ( balance >= money ) {
        balance -= money;
        std::cout << "Amount deducted: " << money << std::endl;
    } else {
        std::cout << "Can not deduct amount of: " << money << std::endl;
    }
    std::cout << "Current balance: " << balance << std::endl;
}

int main()
{
    std::thread t1(redrawMoney, 500);
    std::thread t2(addMoney, 500);

    t1.join();
    t2.join();

    return 0;
}