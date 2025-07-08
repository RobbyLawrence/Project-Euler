#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
 * Problem 27: Quadratic Primes
* I couldn't think of a good strategy for this problem.
* It seems like the whole "prime-generating quadratics" are an actual unsolved problem.
* That is, there's currently no heuristic for determining the number of consecutive primes that
* a quadratic sequence might generate; I think it'll just be a bruteforce problem.
*
* There are definitely ways to speed up the checking process though. Instead of re-evaluating each term in a sequence,
* we'll just increment the b term and increment each term in the current sequence.
*
* To keep things simple, I'll just throw away the sequence and start again when I need to increment the a term.
*
* To be clear, I'm checking all values of a such that -1000 < a < 1000 and b such that -1000 <= b <= 1000.
* I'm counting how many consecutive primes each quadratic expression will generate, starting at n = 0.
*
*/

bool is_prime(int n) {
    n = abs(n); // make sure we aren't taking the square root of negative numbers
    for (int i = 2;i<(int)sqrt(n)+1;i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int evaluate(int a, int b, int term) {
    return term*term + a*term + b;
}

int count_consecutive_primes(int a, int b) {
    int counter = 0;
    int num_primes = 0;
    while (true) {
        int curr_term = evaluate(a,b,counter);
        if (is_prime(curr_term)) {
            num_primes++;
            counter++;
            continue;
        }
        else {
            break;
        }
    }
    return num_primes;
}

int main() {
    int max_primes = 0;
    int best_a,best_b;
    for (int a =-1000;a<1000;a++) {
        for (int b = -1000;b<=1000;b++) {
            int num_primes = count_consecutive_primes(a, b);
            if (num_primes > max_primes) {
                max_primes = num_primes;
                best_a = a;
                best_b = b;
            }
        }
    }

    cout << "Best quadratic: n^2 + " << best_a << "n + " << best_b << endl;
    cout << "Generates " << max_primes << " primes\n";
    cout << "Product of a and b: " << best_a*best_b << '\n';
    return 0;
}
