#include <iostream>
#include <unordered_set>
#include <cmath>
#include <gmpxx.h>

/*
* honestly I think I can just do all of this problem in main.
* doesn't seem like it'll be too difficult.
*
* Ended up deciding to use the GNU multiprecision bignum library
* to make this easy.
*/

namespace std {
    template<>
    struct hash<mpz_class> {
        size_t operator()(mpz_class const& x) const noexcept {
            return hash<std::string>()( x.get_str() );
        }
    };
}
// hash functor for unordered_set

int main() {
    std::unordered_set<mpz_class> distinct;
    for (int a = 2;a<=100;a++) {
        for (int b = 2;b<=100;b++) {
            mpz_class result;
            result = 1;
            for (int i = 0;i<b;i++) {
                result *= a;
            }
            distinct.insert(result);
        }
    }
    std::cout << "Distinct powers: " << distinct.size() << '\n';
    return 0;
}
