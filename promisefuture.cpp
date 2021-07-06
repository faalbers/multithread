#include <iostream>
#include <thread>
#include <future>

typedef long int ull;

void findOdd(std::promise<ull> &&oddSumPromise, ull start, ull end)
{
    ull oddSum = 0;
    for ( ull i = start ; i <= end; ++i ) {
        if ( i & 1 ) oddSum += 1;
    }
    // set the promise once it is ready
    oddSumPromise.set_value(oddSum);
}

int main()
{
    // find odd numbers sum between following 2 numbers
    ull start = 0, end = 1900000000;

    // create promise object to retrieve a promised value of a certain type
    // the promise is passed to the thread to be set when ready
    std::promise<ull> oddSum;

    // create a future from that promise object 
    // the future is used to retrieve the promise when it's ready
    std::future<ull> oddFuture = oddSum.get_future();

    std::cout << "Start Thread !\n";

    // moving oddSum to the thread because it's not needed anymore in main
    std::thread t(findOdd, std::move(oddSum), start, end);

    std::cout << "Waiting for stuff in main to complete\n";

    // wait till the future receives the promise and then continue
    std::cout << "oddSum = " << oddFuture.get() << std::endl;

    t.join();
    std::cout << "Completed !\n";
    return 0;
}