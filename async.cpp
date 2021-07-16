#include <iostream>
#include <thread>
#include <future>

typedef unsigned long int ull;

#define ASYNC 1

std::mutex m;

ull findOddSum(ull start, ull end)
{
    m.lock();
    std::cout << "findOddSum ID: " << std::this_thread::get_id() << std::endl;
    m.unlock();

    ull oddSum = 0;
    for(ull x = start; x <= end; x++) {
        if(x & 1) oddSum += x;
    }
    return oddSum;
}

int main()
{
    ull start = 0;
    ull end = 1900000000;

#if ASYNC
    std:: cout << "Run task async" << std::endl;
    std::future<ull> OddSum = std::async(std::launch::async, findOddSum, start, end);
#else
    std:: cout << "Run task deffered" << std::endl;
    std::future<ull> OddSum = std::async(std::launch::deferred, findOddSum, start, end);
#endif
    m.lock();
    std::cout << "main       ID: " << std::this_thread::get_id() << std::endl;
    m.unlock();

    std::cout << "start pause ...\n";
    std::this_thread::sleep_for (std::chrono::seconds(1));
    std::cout << "end pause ...\n";

    ull oddSum = OddSum.get();

    std::cout << "Result: " << oddSum << std::endl;

    std::cout << "Completed !\n";
    
    return 0;
}