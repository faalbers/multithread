#include "Timer.hpp"
#include <string>
#include <chrono>
#include <iostream>

Timer::Timer (std::string name) : name_(name)
{
    start_ = std::chrono::high_resolution_clock::now();
}

Timer::~Timer ()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_);
    std::cout << "Timer " << name_ << ": " << duration.count() << " ms\n";
}