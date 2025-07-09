/**
 * extern keyword:
 * The extern keyword was inherited from C. It was used to:
 * - declare variables that are defined in another file.
 * - turn the definition of an uninitialized variable into a declaration.
 * - make a global variable accessible across multiple source files.
 *
 * // source1.cpp
 * extern int meaning_of_life; // Declare meaning_of_life
 * meaning_of_life = 42;
 *
 * // source2.cpp
 * extern int meaning_of_life; // Declare meaning_of_life
 * cout << meaning_of_life << endl;
 *
 * // source_impl.cpp. There must be exactly one file where the variable is defined.
 * int meaning_of_life; // Define meaning_of_life. This must not be initialized.
 *
 */

#pragma once
extern int meaning_of_life; // Declare meaning_of_life

// Declare a function
void func();
