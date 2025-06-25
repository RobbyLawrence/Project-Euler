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
    unordered_map<int,vector<int> > sum_factors_map;
    /* Potential Optimization!
     * if this isn't fast enough, I can eliminate parts of the search space by first checking small numbers 2-10, and then the bounds for i
     * are changed to 1 <= i <= ceil(i/10). This would be asymptotically the same, but would speed up the program for this case.
     */
    for (int i = 1;i<100000;i++) {
        int sum_factors = 0;
        int upper_bound = (int)floor((float)i/2 + 0.5);
        for (int j = 1; j <= upper_bound; j++) {
            if (i % j == 0) {
                sum_factors += j;
            }
        }
        map_factors.insert(make_pair(i,sum_factors));
        unordered_map<int,vector<int>>::iterator it = sum_factors_map.find(sum_factors);
        if (it == sum_factors_map.end()) {
            vector<int> vect;
            vect.push_back(i);
            sum_factors_map.insert(make_pair(sum_factors,vect));
        }
        else {
            it->second.push_back(i);
        }
    }
    /*
    for (unordered_map<int,int>::iterator it = map_factors.begin();it != map_factors.end();it++) {
        cout << it->first << ": " << it->second << '\n';
    }

    for (unordered_map<int,vector<int>>::iterator it = sum_factors_map.begin();it != sum_factors_map.end();it++) {
        cout << it->first << ": ";
        for (int element : it->second) {
            cout << element << " ";
        }
        cout << '\n';
    }
    */
    // at this point, both the maps are filled
    // now we just have to do the main traversal
    int total = 0;
    vector<pair<int,int>> amicable_pairs;
    bool previously_seen = false;

    for (int num = 1;num < 100000;num++) {
        unordered_map<int,int>::iterator it = map_factors.find(num);
        previously_seen = false;
        int num_sum = 0;
        if (it == map_factors.end()) {
            continue;
        }
        else {
            num_sum = it->second;
        }
        if (num == num_sum) { // perfect numbers aren't amicable
            continue;
        }
        unordered_map<int,int>::iterator jt = map_factors.find(num_sum);
        if (jt == map_factors.end()) {
            continue;
        }
        if (num == jt->second) {
            for (pair<int,int> entry : amicable_pairs) {
                if (num == entry.first || num == entry.second) {
                    previously_seen = true;
                    break;
                }
            }
            if (previously_seen) {
                continue;
            }
            else {
                amicable_pairs.push_back(make_pair(num,num_sum));
                total += num;
                total += num_sum;
            }
        }
    }
    cout << "Amicable numbers < 10000:\n";
    for (pair<int,int> entry : amicable_pairs) {
        cout << entry.first << ", " << entry.second << endl;
    }
    cout << "Sum: " << total << endl;
    return 0;
}

/*
 * Fun problem! I think the difficulty could've been raised a little higher; I think
 * it would've been reasonable to do 100000 or 200000. Maybe even higher. I had an potential optimization
 * that could've saved a LOT of time; I was doing a lot of unnecessary operations in this program.
 *
 * I still enjoyed this challenge though!
 *
 */
