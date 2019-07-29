#include <assert.h>
#include <iostream>
#include <vector>

static const long long MOD = 998244353;

static const size_t MAX_M = 101 * 5;
static size_t n, m;
static long long  back[MAX_M];

long long bin_pow(long long x, long long d) {
    long long res = 1;
    while (d) {
        if (d & 1) {
            res = (res * x) % MOD;
        }
            x = (x * x ) % MOD;
            d >>= 1;
    }
    return res;
}

long long get_back(long long a) {
   return bin_pow(a, MOD - 2);
}

void some_evaluation() {
    back[0] = 0;
    for (size_t i = 1; i < MAX_M; ++i) {
        back[i] = get_back(i);
    }
}

long long mod(long long number) {
    long long m = number % MOD;
    return m < 0 ? m + MOD : m;
}

void print(const std::vector<long long> &a, size_t m) {
    for (size_t var = 0; var < m; ++var) {
        std::cout << a[var] << " ";
    }
    std::cout << "\n";
}

int main()
{
    some_evaluation();
    std::cin >> n >> m;
    std::vector<long long> P(MAX_M, 0), derivated_P(MAX_M, 0), exponent(MAX_M, 0), ln(MAX_M, 0), sqr(MAX_M, 0);

    std::cin >> P[0];
    for (size_t i = 1; i <= n; ++i) {
        std::cin >>P[i];
        derivated_P[i - 1] = mod(P[i] * i);
    }

    //sqrt(1 + P(t))
    sqr[0] = 1;
    for (size_t i = 1; i < m; ++i) {
        long long tmp  = 0;
        for (size_t j = 1; j < i; ++j) {
            tmp = mod(tmp + sqr[j] * sqr[i - j]);
        }
        sqr[i] = mod((P[i] - tmp) * back[2]);
    }

    print(sqr, m);

    //e^(P(t))
    exponent[0] = 1;
    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 0; j < i; ++j) {
            exponent[i] = mod(exponent[i] + mod(derivated_P[j] * exponent[i - 1 - j]));
        }
        exponent[i] = mod(exponent[i] * back[i]);
    }
    print(exponent, m);

    //ln(1 + P(t))
    P[0] = 1;
    std::vector<long long> inv_P(MAX_M, 0);
    inv_P[0] = 1;

    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 1; j <= i; ++j) {
            inv_P[i] = mod(inv_P[i] + mod(P[j] * inv_P[i - j]));
        }
        inv_P[i] = mod(-inv_P[i]);
    }

    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 0; j < i; ++j) {
            ln[i] = mod(ln[i] + mod(derivated_P[j] * inv_P[i - 1 - j]));
        }
        ln[i] = mod(ln[i] * back[i]);
    }
    print(ln, m);
    return 0;
}

