/**
 * Clocks
 * The std::chrono library provides three types of clocks:
 * 1. std::chrono::system_clock: measures "wall time" using the hardware system clock
 * 2. std::chrono::steady_clock: idealized clock which only goes forward, one tick at a time
 * 3. std::chrono::high_resolution_clock: clock with the shortest tick period supported by system
 *
 * System Clock:
 * The system clock is similar to the C library clock which measures "wall time" using the operating
 * system's clock. It is the best clock for interactive use. Its time points relate to calendars,
 * watches, phones, etc. I.e., it matches the user's perception of time.
 * However, system clock is not well suited for measuring time intervals. The system clock may be
 * corrected if it runs fast or slow. Occasional adjustments for daylight saving time also affect
 * the system clock. Changes may cause the system clock to jump forward or backward.
 *
 * Steady Clock:
 * The steady clock is an idealized clock which only goes forward (monotonically), one tick at a
 * time. It is not affected by changes to the system clock. It is the best clock for measuring time
 * intervals. External events can never cause the clock to jump forward or backward.
 *
 * All three clocks have a static member function `now()` that returns the current time point.
 *
 * Time Point:
 * time_point class represents a point in time. The contains a duration representing the time
 * interval since the clock's epoch. A time_point object is associated with a particular clock type.
 * Two time_point objects can be subtracted to yield a duration object.
 */

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals; // for suffixes (h, min, s, ms, us, ns)

long long fibonacci(long long n) { return (n < 2) ? n : fibonacci(n - 1) + fibonacci(n - 2); }

// g++ -std=c++17 -Wall -Wextra -pedantic 179-chrono_clocks_and_time_points.cpp && ./a.out
int main() {
    auto start = std::chrono::steady_clock::now();

    long long n = fibonacci(45);

    std::cout << "Fibonacci number is " << n << std::endl;

    auto finish = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "Time taken: " << elapsed << " milliseconds" << std::endl;

    /**
     * sleep_for()
     * The thread library provides a function which makes the current thread pause/sleep for a
     * specified duration. In a single-threaded program, this will make the main thread sleep. The
     * actual duration may be longer than requested due to the operating system's scheduling.
     */
    std::cout << "Waiter!" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "You called, sir?" << std::endl;
}
