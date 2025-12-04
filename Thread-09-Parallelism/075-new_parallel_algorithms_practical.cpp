#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

// g++ -std=c++20 -Wall -Wextra -pedantic 075-new_parallel_algorithms_practical.cpp -ltbb && ./a.out
int main() {
    /**
     * std::transform_reduce():
     * - We can use our own binary functions for both the "transform" and "reduce" operations.
     * - The default transform operation is "*" and the default reduce operation is "+".
     *
     * Task: Finds the greatest difference between the elements in two vectors
     */
    std::vector<double> expected{0.1, 0.2, 0.3, 0.4, 0.5};
    std::vector<double> actual{0.09, 0.22, 0.27, 0.41, 0.52};

    auto max_diff = std::transform_reduce(
        std::execution::par, begin(expected), end(expected), begin(actual),

        // Initial value for the largest difference
        0.0,

        //  "Reduce" operation. Find the maximum of two differences
        [](auto diff1, auto diff2) { return std::max(diff1, diff2); },

        // "Transform" operation. Find the absolute difference between two elements
        [](auto exp, auto act) { return std::abs(act - exp); });

    std::cout << "Max difference is: " << max_diff << '\n';
}