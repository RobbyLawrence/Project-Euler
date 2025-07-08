#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
 * Problem 23: Non-Abundant Sums
 * I've got a first idea. This is kind of similar to the
 * amicable pairs problem that I finished earlier today.
 *
 * I'm going to find all abundant numbers from 1-28123.
 * Then, I'm going to initialize an unordered_map<int,bool>,
 * and fill it with {n,false} (such that 1 < n < 28123).
 * As I consider all pairs of the abundant numbers that I previously
 * gathered, I'll mark them as true.
 *
 * Once I've considered all pairs and marked everything that can be
 * written as the sum of abundant numbers, I'll do one last traversal
 * and total all the element that remain false.
 *
 * I actually think I don't need to determine all abundant numbers in the
 * aforementioned range, but I don't see how I could narrow it down meaningfully.
 */

int sum_factors(int num) {
    int sum_factors = 0;
    for (int i = 1;i<=(int)(num/2);i++) {
        if (num % i == 0) {
            sum_factors += i; // add the factor to the sum
        }
    }
    return sum_factors;
}

int main() {
    vector<int> abundant_numbers;
    // I don't think I need to check 28123
    for (int i = 1;i<28123;i++) {
        int sum = sum_factors(i);
        if (sum > i) {
            abundant_numbers.push_back(i);
            // cout << i << endl;
        }
    }

    // initialize that map I talked about earlier
    unordered_map<int,bool> numbers;
    for (int i = 1;i<=28123;i++) {
        numbers.insert(make_pair(i,false));
    }

    // this is so inefficient lol
    // I'll need to make (6965 choose 2) = 24252130 comparisons
    for (int i = 0;i<abundant_numbers.size();i++) {
        for (int j = i;j<abundant_numbers.size();j++) {
            int abundant_sum = abundant_numbers[i] + abundant_numbers[j];
            if (abundant_sum < 28124) { // if we hit a number, we set it to true
                numbers.find(abundant_sum)->second = true;
            }
        }
    }
    // once the above loops finish, we should be able to shake out the non-abundant sums

    int total = 0;
    for (unordered_map<int,bool>::iterator it = numbers.begin();it != numbers.end();it++) {
        if (it->second == false) {
            total += it->first;
        }
    }
    cout << total << '\n';
    return 0;
}

/*
 * this one was sooo easy
 *
 * I think I finished it in like 20-30 minutes. Felt very smart though!
 * I definitely recognize that my solution is terrible lol.
 * I timed the execution and got 0.179 seconds, but I feel like this could be optimized down to
 * around a fourth of that. Not my problem though, onto the next!
 */
