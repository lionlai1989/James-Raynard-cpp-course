#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

// g++ -std=c++20 -Wall -Wextra -pedantic 073-new_parallel_algorithms.cpp -ltbb && ./a.out
int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7};

    /**
     * std::accumulate(): specified to execute sequentially
     * - Performed in left-to-right order, one addition at a time
     *   - ((((0 + 1) + 2) + 3) + ...)
     * - Cannot be parallelized
     *   - Each operation must complete before the next begins
     * - Cannot be vectorized
     *   - Each operation can only take two operands
     */
    std::cout << "The sum of the elements is " << std::accumulate(vec.begin(), vec.end(), 0)
              << '\n';

    /**
     * std::reduce(): reimplementation of std::accumulate(). supports execution policies
     * - `seq`: perform as seven additions
     *   - (0 + 1 + 2 + 3 + 4 + 5 + 6 + 7)
     * - `par`: perform as four parallel additions
     *   - ((0 + 1) + (2 + 3) + (4 + 5) + (6 + 7))
     * - `unseq`: perform as two vectorized additions
     *   - (0 + 1 + 2 + 3) + (4 + 5 + 6 + 7)
     * - `par_unseq`: perform as two parallel vectorized additions
     *   - ((0 + 1 + 2 + 3) + (4 + 5 + 6 + 7))
     *
     * std::reduce() will not give the correct result if:
     * - reordering of operations changes the result, or
     * - regrouping of operations changes the result.
     *
     * The operator used in std::reduce() must be both:
     * - commutative: x + y == y + x
     * - associative: (x + y) + z == x + (y + z)
     *
     * Division and subtraction are neither commutative nor associative. Floating‑point arithmetic
     * is not associative due to rounding errors (and can exhibit surprising behavior with NaNs or
     * signed zeros). For safe parallel reductions, the binary operation must be associative (and
     * ideally commutative) and the initial value must be a true identity for that operation.
     */
    std::cout << "The sum of the elements is "
              << std::reduce(std::execution::par, vec.begin(), vec.end(), 0) << '\n';

    std::vector<int> vec2(vec.size());

    /**
     * std::partial_sum(): cannot be parallelized just like std::accumulate()
     */
    std::partial_sum(vec.begin(), vec.end(), vec2.begin());
    std::cout << "Elements of partial sum vector: ";
    for (auto i : vec2)
        std::cout << i << ", ";
    std::cout << '\n';

    std::vector<int> vec3(vec.size());

    /**
     * std::inclusive_scan(): reimportation of std::partial_sum(). supports execution policies
     */
    std::inclusive_scan(std::execution::par, vec.begin(), vec.end(), vec3.begin());
    std::cout << "Elements of inclusive scan vector: ";
    for (auto i : vec3)
        std::cout << i << ", ";
    std::cout << '\n';

    std::vector<int> vec4(vec.size());

    /**
     * std::exclusive_scan(): similar to std::inclusive_scan(), but excludes the current element and
     * takes an extra value. Use the extra value instead of the current element.
     */
    std::exclusive_scan(std::execution::par_unseq, vec.begin(), vec.end(), vec4.begin(), -1);
    // This is equivalent to
    std::vector<int> vec5{-1, 1, 2, 3, 4, 5, 6};
    std::vector<int> vec6(vec5.size());
    std::inclusive_scan(vec5.begin(), vec5.end(), vec6.begin());
    std::cout << "Elements of exclusive scan vector: ";
    for (auto i : vec4)
        std::cout << i << ", ";
    std::cout << '\n';
    std::cout << "Elements of inclusive scan vector: ";
    for (auto i : vec6)
        std::cout << i << ", ";
    std::cout << '\n';
}