#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
using namespace std;

/*
 * Problem 24: Lexicographic Permutations
* I was going to do this one soley through combinatorics, but decided that
* defeats the purpose. I do know, however, that the number is going to start with a 2.
* This is because there are 10 digits, and if we fix the first digit (for example, if I wanted to know how many
* permutations started with 0), then there are 9! = 362880 permutations.
* Since the permutations are ordered "lexicographically", these come first,
* then the ones that start with a one. There's also 362880 of these. So I know that since the first
* 362880 * 2 permutations either start with a one or a zero, and the next 362880 start with a 2,
* it's guaranteed that the millionth permutation will start with a two. So I'll just search through
* all these. In short, I'm looking for the (1,000,000 - 2*362880)th permutation that starts with a 2.
*
* Update: I made an effort to solve only using combinatorics, and wasn't successful.
* So now I have to write the program lol
*
*/

bool has_double(string number) {
    vector<bool> seen(false,10);
    for (char c : number) {
        if (seen[(int)c]) {}
    }
}

int main() {
    vector<int> digits = {0,1,2,3,4,5,6,7,8,9};
    vector<int> permutations;
    while (true) {

    }
    return 0;
}
