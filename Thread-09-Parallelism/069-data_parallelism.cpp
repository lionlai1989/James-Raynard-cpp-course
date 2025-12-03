/**
 * Concurrency vs. Parallelism in two sentences:
 * - Concurrency is about dealing with distinct tasks at once which could run on a single core.
 * - Parallelism is about doing the same task at the same time on multiple cores.
 *
 * Parallelism Overview:
 * - Task Parallelism: subtasks run on separate threads in parallel.
 *
 * - Data Parallelism: subsets of data are processed on separate threads in parallel.
 *   - vectorization, SIMD
 *   - Improved data locality. E.g., given 32 MB of data and 4 cores with 8 MB cache each, each core
 *     can cache its own 8 MB subset. It does not need to fetch data from RAM or interact with cache
 *     controller.
 *
 * - Pipeline Parallelism: A task is divided into stages, and different stages are processed in
 *   parallel.
 * - Graph Parallelism: Similar to pipeline parallelism, but the stages form a graph instead of a
 *   single stream of stages.
 */

#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

// Compute the sum of a range of elements
double accum(double *beg, double *end) { return std::accumulate(beg, end, 0.0); }

// Divide the data into 4 subsets using std::async
//
// PROS:
// - Simpler, cleaner code with less boilerplate
// - Automatic thread management (runtime decides when to create threads)
// - Exception safety: futures automatically propagate exceptions from tasks
// - Less verbose than packaged_task + thread
//
// CONS:
// - Less control: cannot manage thread lifecycle explicitly
// - Less flexible: harder to do advanced coordination (e.g., interleave work)
// - Implicit thread creation depends on launch policy
//
// BLOCKING: YES
// - Blocks at fut1.get() + fut2.get() + ... (waits for all tasks to complete)
// - Suitable for simple fire-and-forget parallel computation
double add_parallel(std::vector<double> &vec) {
    // Find the first element of the vector
    double *vec0 = &vec[0];

    // Find the number of elements
    auto vsize = vec.size();

    // Start the threads
    // Pass the subset's range as argument to the task function
    auto fut1 = std::async(std::launch::async, accum, vec0, vec0 + vsize / 4);
    auto fut2 = std::async(std::launch::async, accum, vec0 + vsize / 4, vec0 + 2 * vsize / 4);
    auto fut3 = std::async(std::launch::async, accum, vec0 + 2 * vsize / 4, vec0 + 3 * vsize / 4);
    auto fut4 = std::async(std::launch::async, accum, vec0 + 3 * vsize / 4, vec0 + vsize);

    // Reduce step. Combine the results for each subset
    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

// Divide the data into 4 subsets using std::packaged_task + std::thread
//
// PROS:
// - Explicit control: you manage thread creation, start, and join explicitly
// - More flexible: can set thread properties (affinity, priority), detach threads, or coordinate
// multiple tasks
// - Better for complex parallel patterns (task parallelism, pipelines, thread pools)
// - Transparent thread lifecycle: clear when threads are created and destroyed
//
// CONS:
// - More boilerplate: need packaged_task, std::thread, explicit join calls
// - Manual exception handling: must catch exceptions from get() manually
// - Requires std::move: packaged_task is move-only, easy to forget
// - Risk of bugs: forgetting join() leads to undefined behavior
//
// BLOCKING: YES
// - Blocks at thr.join() calls (waits for all threads to complete)
// - Then blocks at fut.get() calls (waits for results from futures)
// - More explicit control over when blocking occurs compared to std::async
double add_parallel2(std::vector<double> &vec) {
    // Type alias to simplify the code
    using task_type = double(double *, double *);

    // Packaged tasks to manage each thread
    std::packaged_task<task_type> ptask1(accum);
    std::packaged_task<task_type> ptask2(accum);
    std::packaged_task<task_type> ptask3(accum);
    std::packaged_task<task_type> ptask4(accum);

    // Future objects for each thread's result
    auto fut1 = ptask1.get_future();
    auto fut2 = ptask2.get_future();
    auto fut3 = ptask3.get_future();
    auto fut4 = ptask4.get_future();

    // Find the first element of the vector
    double *vec0 = &vec[0];

    // Find the number of elements
    auto vsize = vec.size();

    // Start the threads
    // Pass the subset's range as argument to the task function
    std::thread thr1(std::move(ptask1), vec0, vec0 + vsize / 4);
    std::thread thr2(std::move(ptask2), vec0 + vsize / 4, vec0 + 2 * vsize / 4);
    std::thread thr3(std::move(ptask3), vec0 + 2 * vsize / 4, vec0 + 3 * vsize / 4);
    std::thread thr4(std::move(ptask4), vec0 + 3 * vsize / 4, vec0 + vsize);

    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();

    // Reduce step. Combine the results for each subset
    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

// g++ -std=c++20 -Wall -Wextra -pedantic 069-data_parallelism.cpp && ./a.out
int main() {
    /**
     * Data Parallelism Example
     */
    // Populate a vector with elements 1.0, 2.0, ..., 16.0
    std::vector<double> vec(16);
    std::iota(vec.begin(), vec.end(), 1.0);

    // Populate a vector with 10,000 random elements
    std::vector<double> vrand(10'000);
    std::generate(vrand.begin(), vrand.end(), [&vrand]() { return dist(mt); });

    // Do the calculations
    std::cout << "Sum of first 16 integers: " << add_parallel(vec) << '\n';
    std::cout << "Sum of 10,000 random numbers: " << add_parallel(vrand) << '\n';
    std::cout << "Sum of first 16 integers: " << add_parallel2(vec) << '\n';
    std::cout << "Sum of 10,000 random numbers: " << add_parallel2(vrand) << '\n';
}