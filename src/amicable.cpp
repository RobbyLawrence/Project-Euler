#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
 * The main thing I'm worried about here is computation time.
 *
 * Okay I thought about it for a little bit, and have decided on a strategy.
 *
 * I'm going to go through all the numbers under 10000 and determine the sum of factors for each number.
 * I thought about using Sieve of Eratosthene's or Pollard's Rho, but I don't want to implement all that.
 *
 * I'll test all numbers less than sqrt(n). I'll keep a running total of the sum. Then,
 * I'll insert that into an unordered_map<int,int> that maps number to sum of factors,
 * and also update an unordered_map<int,unordered_set<int>>, where the key is the sum of factors, and we'll insert the
 * number into the value-unordered_set. That'll give fast-lookup times when searching for pairs.
 */
int main() {
    // first, i need to make an unordered_map<int,int> that maps each number to the sum of its factors
    unordered_map<int,int> map_factors;
    for (int i = 1;i<10;i++) {
        int sum_factors = 0;

        int limit = static_cast<int>(std::sqrt(i));
        for (int j = 1; j <= limit; ++j) {
            if (i % j == 0) {
                sum_factors += j;
                int other = i / j;
                if (other != j)            // don’t add the square root twice
                    sum_factors += other;
            }
        }
        map_factors.insert(make_pair(i,sum_factors));
    }
    for (unordered_map<int,int>::iterator it = map_factors.begin();it != map_factors.end();it++) {
        cout << it->first << ": " << it->second << '\n';
    }

    return 0;
}
