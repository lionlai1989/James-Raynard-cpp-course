#include "Date.h"
#include "Date_impl.h"

// Implemented using RAII
Date::Date(int day, int month, int year) {
    // Allocate in constructor
    pImpl = std::make_unique<Date_impl>(day, month, year);
}

Date::~Date() = default;

Date::Date(Date &&) noexcept = default;
Date &Date::operator=(Date &&) noexcept = default;

void Date::set_day(int day) { pImpl->set_day(day); }
void Date::print() { pImpl->print(); }
