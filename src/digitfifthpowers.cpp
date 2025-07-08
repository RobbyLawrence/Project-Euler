#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int digit_fifth_power(int num){
    string num_string = to_string(num);
    int total = 0;
    for (char digit : num_string) {
        int d = digit - '0';
        total += d*d*d*d*d;
    }
    return total;
}

int main() {
    unordered_map<int,int> near;
    vector<int> exact;
    for (int i = 0;i<1000000;i++) {
        int result = digit_fifth_power(i);
        cout << i << " -> " <<  result << '\n';
        int difference = i - result;

        if (abs(difference) < 10) {
            near.insert(make_pair(i,result));
            if (difference == 0) {
                exact.push_back(i);
            }
        }
    }
    cout << "Exact:\n";
    int total = 0;
    for (int element : exact) {
        cout << element << '\n';
        total += element;
    }
    total -= 1;
    cout << total << endl;
}

/*
 * I was struggling on this, until I realized that eventually
 * there's no chance for the sum of 5th powers to catch up to the actual number,
 * since the largest n digit number 5th power sum is n*9^5, and the smallest n digit number is 10^(n-1).
 * Once 10^(n-1)>n*9^5, a number's sum of digit's 5th powers will never be greater than the number itself.
 *
 * After I figured that out, it was just a bruteforce.
 */
