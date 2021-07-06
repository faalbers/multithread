#include <iostream>
#include <thread>
#include <chrono>

void run(int count)
{
    while (count --> 0) std::cout << "Thread running: " << count << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // If using detach it will never reach the end of the thread
    std::cout << "Thread Finished\n";
}

int main()
{
    std::thread t(run, 10);
    std::cout << "in main()\n";

    // detach thread from parent thread only if it is joinable
    // since main now ends before thread is done, thread does not finish
    if (t.joinable()) t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // wait for thread to be done only if it is joinable
    if (t.joinable()) t.join();

    std::cout << "main() done\n";
    return 0;
}