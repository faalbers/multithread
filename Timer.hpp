#ifndef _TIMER_H_
#define _TIMER_H

#include <string>
#include <chrono>

class Timer
{
public:
    Timer (std::string name);
    ~Timer();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::string name_;
};

#endif