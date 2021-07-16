#include <iostream>
#include <future>

typedef unsigned long int ull;

#define ASYNC 0

ull findOddSum(ull start, ull end)
{
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
#else
    std:: cout << "Run task deffered" << std::endl;
    std::future<ull> OddSum = std::async(std::launch::deferred, findOddSum, start, end);
#endif
    
    return 0;
}