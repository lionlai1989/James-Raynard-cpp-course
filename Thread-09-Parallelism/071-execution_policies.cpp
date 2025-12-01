/**
 * Code Execution: modern computers support four code execution models:
 * 1. Sequential execution: Code is executed one statement after another in a single thread.
 * 2. Parallel execution: Code is executed simultaneously on multiple threads.
 * 3. Vectorized execution: Code is executed using SIMD (Single Instruction, Multiple Data)
 *    instructions that operate on multiple data points in a single instruction cycle.
 * 4. Parallel + Vectorized execution: Code is executed using multiple threads, each utilizing
 *    SIMD instructions.
 *
 * In C++17, the Standard Library introduced execution policies to specify how algorithms
 * should be executed. The execution policies are defined in the <execution> header and include:
 * - std::execution::seq: Specifies sequential execution.
 * - std::execution::par: Specifies parallel execution.
 * - std::execution::unseq: Specifies vectorized execution.
 * - std::execution::par_unseq: Specifies parallel and vectorized execution.
 * There "requests" may be ignored by the implementation if it cannot support them.
 *
 */

#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread -ltbb 071-execution_policies.cpp && ./a.out
int main() {
    /**
     * Sequential execution:
     * All operations are performed on a single thread, the thread which calls the algorithm.
     * Operations will not be interleaved. They may not necessarily be performed in a specific
     * order.
     */
    std::vector<int> vec{3, 1, 4, 1, 5, 9};
    std::sort(std::execution::seq, vec.begin(), vec.end(), [](int a, int b) { return b < a; });
    for (auto i : vec)
        std::cout << i << ',';
    std::cout << '\n';

    /**
     * Parallel execution:
     * - Operations perform in parallel across multiple threads.
     * - Guarantees:
     *   - An operation will run on the same thread for its entire duration.
     *   - Operations perform on the same thread will not be interleaved.
     *   - Operations may not necessarily be performed in a specific order.
     * - Cautions:
     *   - operations perform on different threads may interleave.
     *   - The programmer MUST prevent data races.
     * `count` is shared between multiple threads without synchronization. This causes a data race.
     */
    std::vector<int> vec2(20'000);
    int count = 0;
    std::for_each(std::execution::par, vec2.begin(), vec2.end(), [&count](int &x) { x = ++count; });
    for (auto i : vec2)
        std::cout << i << ',';
    std::cout << '\n';

    /**
     * Unsequenced execution:
     * - Operations are performed on a single thread, which calls the algorithm.
     * - Guarantees:
     *   - Operations will not be interleaved.
     * - Cautions:
     *   - Operations may not necessarily be executed in a specific order.
     *   - The programmer MUST avoid any modification of shared state between elements or between
     *     threads, such as mutexes, locks, or other synchronization mechanisms.
     *   - Memory allocation and deallocation are not allowed.
     */
    std::vector<int> vec3{3, 1, 4, 1, 5, 9};
    std::sort(std::execution::unseq, vec3.begin(), vec3.end(), [](int a, int b) { return b < a; });
    for (auto i : vec3)
        std::cout << i << ',';
    std::cout << '\n';

    /**
     * Unsequenced execution:
     * - Operations perform in parallel across multiple threads.
     * - Cautions:
     *   - Operations perform on the same thread may be interleaved.
     *   - They may not necessarily be executed in a specific order.
     *   - An operation may be migrated from one thread to another.
     *   - The programmer MUST avoid any modification of shared state between elements or between
     *     threads, such as mutexes, locks, or other synchronization mechanisms.
     */
    std::vector<int> vec4{3, 1, 4, 1, 5, 9};
    std::sort(std::execution::par_unseq, vec4.begin(), vec4.end(),
              [](int a, int b) { return b < a; });
    for (auto i : vec4)
        std::cout << i << ',';
    std::cout << '\n';
}
