/**
 * We usually put a full template definition in the header. The reason is that compilers need
 * to know the full definition of the template in order to instantiate the template. Givne an
 * example:
 *
 * // Header.h
 * template <typename T> void func(arg<T>) {..}
 *
 * // File_001.cpp
 * func(this_string); // instantiates func(string) in File_001.cpp
 * ...
 * // File_269.cpp
 * func(that_string); // instantiates func(string) in File_269.cpp
 *
 * The compiler will instantiate a separate copy of func(string) in every File_xxx.cpp.
 * Every File_xxx.o will contain the binary code for func(string). However, the linker will remove
 * the duplicate copies of func(string) in the final executable.
 * However, this "template bloat" increases the size of object files and compile time which can be a
 * serious problem in large projects.
 *
 */

#include <iostream>
#include <string>

// Template declaration only
template <typename T> std::ostream &print(std::ostream &os, const T &t);

// Declare non-template function
void func(const std::string &str);
