/**
 * Semaphore
 * - has a counter, non-negative integer
 * - acquire() decreases the counter
 * - release() increases the counter
 * - when the counter is zero, acquire() blocks and waits until the counter becomes positive.
 *
 * Why uses semaphore?
 * - More flexible
 * - Simpler code
 * - Performance
 * - More versatile
 *
 * Read "The Little Book of Semaphores" for more details.
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Semaphore {
  private:
    std::mutex mtx;
    std::condition_variable cv;
    int counter{0};

  public:
    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Adding one item" << std::endl;

        ++counter;
        count();

        cv.notify_all();
    }

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Removing one item" << std::endl;

        while (counter == 0) {
            cv.wait(lock);
        }

        --counter;
        count();
    }

    void count() const {
        std::cout << "Value of counter: ";
        std::cout << counter << std::endl;
    }
};

class BinarySemaphore {
  private:
    std::mutex mtx;
    std::condition_variable cv;
    int counter{0};
    const int max_count{1};

  public:
    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Adding one item" << std::endl;

        if (counter < max_count) {
            ++counter;
            count();
        }

        cv.notify_all();
    }

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Removing one item" << std::endl;

        while (counter == 0) {
            cv.wait(lock);
        }

        --counter;
        count();
    }

    void count() const {
        std::cout << "Value of counter: ";
        std::cout << counter << std::endl;
    }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 081-semaphore.cpp && ./a.out
int main() {

    Semaphore sem;

    auto insert = [&sem]() {
        sem.release();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    auto relinquish = [&sem] {
        sem.acquire();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    std::vector<std::thread> tasks;

    for (int i = 0; i < 2; ++i)
        tasks.push_back(std::thread(insert));
    for (int i = 0; i < 4; ++i)
        tasks.push_back(std::thread(relinquish));
    for (int i = 0; i < 3; ++i)
        tasks.push_back(std::thread(insert));
    for (auto &task : tasks) {
        task.join();
    }

    std::cout << "--------------------------------" << std::endl;

    BinarySemaphore sem2;

    auto insert2 = [&sem2]() {
        sem2.release();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    auto relinquish2 = [&sem2] {
        sem2.acquire();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    std::vector<std::thread> tasks2;

    for (int i = 0; i < 2; ++i)
        tasks2.push_back(std::thread(insert2));
    for (int i = 0; i < 4; ++i)
        tasks2.push_back(std::thread(relinquish2));
    for (int i = 0; i < 3; ++i)
        tasks2.push_back(std::thread(insert2));
    for (auto &task : tasks2) {
        task.join();
    }
}
