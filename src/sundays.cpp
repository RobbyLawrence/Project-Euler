#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
 * How to solve this problem...
 * I feel like the easiest way to do this might be to
 * have a "day" variable, and add the number of days in the next month to it.
 * After that, I take that modulo 7.
 *
 * I did a little bit of testing. To determine the day of the month that the first of the month falls on,
 * if you have the day that the previous month starts on, do (curr_day + num_days) % 7
 *
 */
static const unordered_map<string,int> months = {
    {"January", 31}, {"February", 28}, {"March",31}, {"April",30}, {"May",31},
    {"June", 30}, {"July",31}, {"August", 31}, {"September",30}, {"October", 31},
    {"November", 30}, {"December", 31},
};

static const unordered_map<int,string> days = {
    {0,"Sunday"},{1,"Monday"},{2,"Tuesday"},{3,"Wednesday"},{4,"Thursday"},{5,"Friday"},{6,"Saturday"}
};

int next_first(int curr_day, string month, int year) {
    int num_days = months.find(month)->second;
    // leap year logic
    if (month == "February") {
        if (year % 4 == 0) {
            // leap year
            num_days++;
            if (year % 100 == 0) {
                // not a leap year
                num_days--;
                if (year % 400 == 0) {
                    // back to being a leap year
                    num_days++;
                }
            }
        }
    }
    int next_first = (curr_day + num_days) % 7;
    return next_first;
}
int main() {
    int first_day = 2; // 01/01/1901 was a Tuesday
    vector<string> months = {"January","February","March","April","May","June",
        "July","August","September","October","November","December"};

    int num_sundays = 0;
    for (int year = 1901;year<=2000;year++) {
        for (string month : months) {
            first_day = next_first(first_day, month, year);
            if (first_day == 0) {
                num_sundays++;
                cout << month << " 1st, " << year << " was a Sunday\n";
            }
        }
    }
    cout << num_sundays << '\n';
    return 0;
}

/*
 * Did not enjoy this problem very much.
 * Not very difficult, but pretty tedious.
 */
