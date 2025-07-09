/**
 * extern template:
 * extern keyword can also apply to templates. We first define a template body (a class or a
 * function) in a header file. And then we declare the instantiation as an extern template.
 *
 * // Header.h:
 * template <typename T> void func(arg<T>) {..} // Define the template body.
 * extern template void func(string); // Declare func(string) as instantiated in another file.
 *
 * // In File_xxx.cpp:
 * // func(string) is called. The compiler will not instantiate func(string) in this file because
 * // it knows that the instantiation happens in another file.
 * func(this_string);
 *
 * // Impls.cpp:
 * // There must be exactly one file where the function is instantiated.
 * template void func(string); // Compiler will instantiate func(string) here.
 *
 *
 * The whole process also works for class templates.
 * // Header.h:
 * template <typename T> class Test {..} // Define the class body.
 * extern template class Test<int>; // Declare Test<int> as instantiated elsewhere.
 *
 * // In File_xxx.cpp:
 * Use Test<int> which is instantiated elsewhere.
 *
 * // Impls.cpp:
 * template class Test<int>; // Compiler will instantiate Test<int> here.
 *
 */

#include <iostream>
#include <string>

template <typename T> std::ostream &print(std::ostream &os, const T &t) { return os << t; }

extern template std::ostream &print(std::ostream &os, const std::string &str);

void func(const std::string &str);