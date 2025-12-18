/**
 * std::chrono is defined in <chrono>, in the `std::chrono` namespace.
 * It has three important concepts:
 * - Clock
 *   - Start date (epoch) and tick rate
 *   - C's clock started on 1 January 1970 and ticks once per second
 * - Time point
 *   - The number of clock ticks since the epoch, at a given point in time
 * - Duration
 *   - An interval of time between two time points, measured in a given clock's time unit
 */
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::literals; // For suffixes (h, min, s, ms, us, ns)

void func(chrono::seconds sec) { cout << sec.count() << " seconds\n"; }

// g++ -std=c++17 -Wall -Wextra -pedantic 178-chrono_duration_types.cpp && ./a.out
// g++ -std=c++20 -Wall -Wextra -pedantic 178-chrono_duration_types.cpp && ./a.out
int main() {
    /**
     * The following line does not zero-initialize the value. It leaves it holding garbage data.
     */
    chrono::seconds s;
    // cout << "Uninitialized seconds variable has value " << s << endl; // C++17 compile error.
    // C++20 compile OK
    cout << "Uninitialized seconds variable has value " << s.count() << endl; // Undefined Behavior

    cout << "\n";

    chrono::hours hour = 5h;
    chrono::minutes min = 10min;
    chrono::seconds sec = 2s;
    chrono::milliseconds msec = 20ms;
    chrono::microseconds usec = 50us;
    chrono::nanoseconds nsec = 80ns;
    cout << "hour = " << hour.count() << " hours " << endl;
    cout << "min = " << min.count() << " minutes " << endl;
    cout << "sec = " << sec.count() << " seconds " << endl;
    cout << "msec = " << msec.count() << " milliseconds " << endl;
    cout << "usec = " << usec.count() << " microseconds " << endl;
    cout << "nsec = " << nsec.count() << " nanoseconds " << endl;

    cout << "\n";

    auto s1 = 2s;
    auto s2 = 3s;
    cout << "s1 = " << s1.count() << endl; // 2
    cout << "s2 = " << s2.count() << endl; // 3
    auto s3 = s1 + s2;
    cout << "s3 = " << s3.count() << endl; // 5
    auto s4 = s3 + 42ms;
    cout << "s4 = " << s4.count() << endl; // 5042

    cout << "\n";

    // chrono::seconds sec2 = 2; // conversion from ‘int’ to non-scalar type ‘std::chrono::seconds’
    chrono::seconds sec2 = 2s; // OK
    // func(2); // could not convert ‘2’ from ‘int’ to ‘std::chrono::seconds’
    func(2s); // OK

    cout << "\n";

    // Conversion between durations can be done implicitly if there is no data loss.
    chrono::seconds s5 = 1h; // OK, h == 3600 seconds
    cout << "s5 = " << s5.count() << " seconds" << endl;

    // chrono::seconds s6 = 5043ms; // Error - data would be lost

    // However, we can use duration_cast to convert durations explicitly.
    chrono::seconds s7 = chrono::duration_cast<chrono::seconds>(5043ms);
    cout << "5043ms converted to " << s7.count() << " seconds\n";
    chrono::seconds s8 = chrono::duration_cast<chrono::seconds>(-5043ms);
    cout << "-5043ms converted to " << s8.count() << " seconds\n";
}
