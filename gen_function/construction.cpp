#include <iostream>
#include <string>
#include <vector>
static const size_t N = 7;
typedef std::vector<long long> pol;
/*
 *  L - Seq
 *  S - MSet
 *  P - Pair
*/

long long C(long long n, long long k) {
    if (k > n) return 0;

    long long res = 1;
    for (size_t i = n - k + 1; i <= n; ++i) {
        res *= i;
    }
    for (size_t i = 1; i <= k; ++i) {
        res /= i;
    }

    return res;
}

pol seq(const pol& p) {
   pol sequence(N, 0);

   sequence[0] = 1;
   for (size_t i = 1; i < N; ++i) {
       for (size_t j = 1; j <= i; ++j) {
           sequence[i] += p[j] * sequence[i - j];
       }
   }
   return sequence;
}

pol set(const pol &p) {
    std::vector<pol> multiset(N, pol(N, 0));
    pol Mset(N, 0);
    multiset[0][0] = 1;
    Mset[0] = 1;

    for (size_t i = 1; i < N; ++i) {
        multiset[0][i] = 1;
    }
    for(long long n = 1; n < N; ++n) {
        for (long long k = 1; k < N; ++k) {
            for (long long j = 0; j <= static_cast<long long>(n/k); ++j) {
                long long comb = (p[k] + j == 0 ? 1 : C(p[k] + j - 1, j));
                multiset[n][k] += comb * multiset[n - k * j][k - 1];
            }

        }
        Mset[n] = multiset[n][n];
    }
    return Mset;
}

pol pair(const pol &p1, const pol &p2) {
    pol pair_pol(N, 0);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            pair_pol[i] += p1[j] * p2[i - j];
        }
    }
    return pair_pol;
}

char get_c() {
    char c;
    std::cin >> c;
    while (isspace(c)) {
        std::cin >> c;
    }
    return c;
}

pol run() {
    char c = get_c();

    switch (c) {
    case 'B': {
        pol p(N, 0);
        p[1] = 1;
        return p;
    }
    case 'L': {
        get_c();
        pol p = run();
        get_c();
        p[0] = 0;
        return seq(p);
    }
    case 'S': {
        get_c();
        pol p = run();
        get_c();
        p[0] = 0;
        return set(p);
    }
    case 'P' :{
        get_c();
        pol p1 = run();
        get_c();
        pol p2 = run();
        get_c();
        return pair(p1, p2);
    }
    default:
        return {0,0,0,0,0,0,0};
    }
}

int main() {
    pol ans = run();
    for (size_t i = 0; i < N; ++i) {
        std::cout << ans[i] << " ";
    }
    return 0;
}
