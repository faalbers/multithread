
#include <iostream>
#include <thread>
#include <atomic>

void update(std::atomic<int> &a) {
    for (int i = 0; i < 100000; ++i) {
        ++a;
    }
}

void single_thread() {
    std::atomic<int> a, b, c, d;
    a = b = c = d = 0;

    // Update 4 variables sequentially
    update(a);
    update(b);
    update(c);
    update(d);
}

void false_sharing() {
    // Create a single atomic integer
    std::atomic<int> a, b, c, d;
    a = b = c = d = 0;

    // Assign each atomic<int> to each thread
    //std::thread t1(update, std::ref(a));
    std::thread t1([&]() {update(a);});
    std::thread t2([&]() {update(b);});
    std::thread t3([&]() {update(b);});
    std::thread t4([&]() {update(d);});

    // Join the 4 threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void print() {
  std::atomic<int> a, b, c, d;
  
  // Return addresses of atomic variables
  std::cout << "Address of a is: " << &a << '\n';
  std::cout << "Address of b is: " << &b << '\n';
  std::cout << "Address of c is: " << &c << '\n';
  std::cout << "Address of d is: " << &d << '\n';
}

int main()
{
    //single_thread();
    //false_sharing();
    print();

    return 0;
}