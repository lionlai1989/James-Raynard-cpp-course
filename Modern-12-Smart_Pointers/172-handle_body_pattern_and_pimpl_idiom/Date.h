#ifndef Date_H
#define Date_H

#include <memory> // unique_ptr

class Date_impl;

/**
 * The Handle class provides the interface to clients. This class cannot be copied because pImpl
 * cannot be copied (unique_ptr is move-only).
 */
class Date {
  private:
    std::unique_ptr<Date_impl> pImpl;

  public:
    Date(int day, int month, int year);
    ~Date();

    Date(Date &&) noexcept;            // Move constructor
    Date &operator=(Date &&) noexcept; // Move assignment operator

    void set_day(int day);
    void print();
};

#endif // Date_H
