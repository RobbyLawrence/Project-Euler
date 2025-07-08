#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

/*
 * Problem 101: Optimum Polynomial
* Started coding before I even started thinking about this one lol
* It seems obvious that there are going to be 10 FITs.
* The only hard part is finding the FITs.
*
* Simplify the problem first. Write a function that, given a sequence of n numbers, will return the (n+1)th
* number that would be given by a (n-1) degree polynomial fitted to the sequence.
*/


typedef long double BIG;

BIG evaluate(BIG n) {
    return 1 - n + pow(n,2) - pow(n,3) + pow(n,4) - pow(n,5)
    + pow(n,6) - pow(n,7) + pow(n,8) - pow(n,9) + pow(n,10);
}

BIG guess_next(vector<BIG> sequence) {
    /*
    * my main strategy here is NOT to use regression and evaluate the resulting polynomial
    *
    * that would be slow
    *
    * instead, I'll find all the differences of the numbers, and then the differences of the differences, and then... ad infinitum.
    * I'll continue that process until the differences vector has length 1, and then walk back down the differences "pyramid",
    * using the information from above to fill in missing information.
    * example:
    * sequence: 0, 12, 14, 16
    * diff_1: 12, 2, 2
    * diff_2: -10, 0
    * diff_3: 10
    *
    * predict diff_2 next: -10, 0, 10
    * predict diff_1 next: 12, 2, 2, 12
    * predict sequence next: 0, 12, 14, 16, 28
    *
    * and 28 is correct for predicting the next term that a cubic polynomial would give us here.
    */

    if (sequence.size() == 1) {
        cout << "hit single case\n";
        return sequence[0];
    }

    vector<vector<BIG> > diff_vect;
    vector<BIG> curr_diffs;

    diff_vect.push_back(sequence);
    // initialize curr_diffs with diff_1, and put that in the diff_vect
    for (int i = 0;i<sequence.size()-1;i++) {
        curr_diffs.push_back(sequence[i+1] - sequence[i]);
    }

    diff_vect.push_back(curr_diffs);

    while (curr_diffs.size() != 1) {
        // curr_diffs should shrink by one after each iteration
        vector<BIG> temp;
        for (int i = 0;i < curr_diffs.size() - 1;i++) {
            temp.push_back(curr_diffs[i+1] - curr_diffs[i]);
        }
        curr_diffs = temp;
        temp.clear();
        diff_vect.push_back(curr_diffs);
    }
    // diff_vect now has the "difference pyramid"
    for (int i = diff_vect.size() - 1;i > 0;i--) {
        // adds last element from current line to last element
        diff_vect[i-1].push_back(diff_vect[i-1][diff_vect[i-1].size() - 1] + diff_vect[i][diff_vect[i].size() - 1]);
    }

    for (vector<BIG> vect : diff_vect) {
        for (BIG entry : vect) {
            cout << entry << " ";
        }
        cout << '\n';
    }

    return diff_vect[0][diff_vect[0].size() - 1];
}

int main() {
    vector<BIG> sequence;
    for (int i = 1;i<=10;i++) {
        BIG val = evaluate(i);
        sequence.push_back(val);
        cout << val << " ";
    }
    cout << '\n';

    vector<BIG> fits;
    BIG fit_total = 0;
    // i'll find the FITs below
    for (int i = 1;i<=10;i++) {
        vector<BIG> subvect(sequence.begin(),sequence.begin() + i);
        cout << "currently on " << i << '\n';
        BIG next = guess_next(subvect);
        if (next != sequence[i+1]) {
            fits.push_back(next);
            fit_total += next;
        }
        else {
            cout << "this shouldn't have happened; verify. occurred on " << subvect.size() - 1 << " as last term\n";
        }
    }
    cout << setprecision(11)<<"FITs total: " << fit_total << '\n';
}


/*
 * very very fun problem, enjoyed it so much.
 * glad that I could make use of a pattern that I noticed when I was much younger.
 */
