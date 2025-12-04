#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

// g++ -std=c++20 -Wall -Wextra -pedantic 074-new_parallel_algorithms_contd.cpp -ltbb && ./a.out
int main() {
    std::vector<int> vec1{1, 2, 3, 4};

    std::vector<int> vec2;
    vec2.reserve(vec1.size()); // allocate memory but do not chnange the `size()`

    /**
     * std::transform(): applies a given function to a range of elements and stores the result in a
     * destination container. similar to `map()` in Python.
     */
    std::transform(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](int n) { return 2 * n; });
    std::cout << "Output vec2: ";
    for (auto i : vec2)
        std::cout << i << ", ";
    std::cout << '\n';

    // Subtract vectors element-wise using std::transform with two input containers
    std::vector<int> vec3{5, 6, 7, 8};
    std::vector<int> vec4;
    std::transform(vec1.begin(), vec1.end(), vec3.begin(), std::back_inserter(vec4),
                   [](int n1, int n2) { return n1 - n2; });
    std::cout << "Output vec4: ";
    for (auto i : vec4)
        std::cout << i << ", ";
    std::cout << '\n';

    /**
     * Transform and Reduce Pattern: (also known as Map-Reduce)
     * - Also known as Map-Reduce
     *   - Divide the data into subsets
     *   - Start a thread for each subset
     *   - Each thread applies a transformation to its subset (Transform)
     *   - transform() performs operations on the thread's subset independently
     *   - Call reduce() to combine each thread's results into a final result (Reduce)
     * The issue with the above implementation is that using two separate algorithms, transform()
     * and reduce(), can slow things down.
     *
     * In C++17, std::transform_reduce() combines both operations into a single algorithm. It's a
     * more powerful and efficient version of std::inner_product().
     *
     * std::inner_product is a specific algorithm designed to compute an inner product (dot product)
     * in a strict, sequential order. It makes no requirements about the associativity or
     * commutativity of the operations, so it always performs the calculations exactly from
     * beginning to end, one by one.
     *
     * std::transform_reduce is a more general "map-reduce" paradigm function, part of the parallel
     * algorithms library. It applies a transform to pairs of elements and then reduces the results.
     * Crucially, to allow for parallel execution, it requires the provided reduction and
     * transformation operations to be associative and commutative. This allows the library
     * implementation to permute and aggregate the results in an unspecified order for efficiency.
     *
     */
    std::vector<int> x{1, 2, 3, 4, 5};
    std::vector<int> y{5, 4, 3, 2, 1};

    auto result = std::inner_product(x.begin(), x.end(), // Iterator range for first vector
                                     y.begin(),          // Start of second vector
                                     0);                 // Initial value of sum

    auto result2 = std::transform_reduce(std::execution::par,     // Execution policy
                                         x.begin(), x.end(),      // Iterator range for first vector
                                         y.begin(),               // Start of second vector
                                         0);                      // Initial value of sum
    std::cout << "Result of inner_product is " << result << '\n'; // Displays 35
    std::cout << "Result of transform_reduce is " << result2 << '\n'; // Displays 35
}
