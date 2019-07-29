#include <vector>
#include <iostream>

static const long long MOD = 104857601;
static const size_t max_size = 2001;
long long mod(long long x) {
    long long m = x % MOD;
    return m >= 0 ? m : MOD + m;
}
int main() {
    long long  n, k;

    std::cin >> k >> n;
    --n;
    std::vector<long long> a(max_size, 0), c(max_size, 0), neg_c(max_size, 0), R(max_size, 0);


    for (size_t i = 0; i < k; ++i) {
        std::cin >> a[i];
    }

    c[0] = 1;
    for (size_t i = 1; i <= k; ++i) {
        std::cin >> c[i];
        c[i] = mod(-c[i]);
    }


    while(n >= k) {
        for (long long i = k; i < 2 * k; ++i) {
            long long s = 0;
            for (long long j = 1; j <= k; ++j)
                s = mod(s - mod(c[j] * a[i - j]));
            a[i] = s;
        }
        size_t last = 0;
        for (int i = 0; i < 2 * k; ++i) {
            if (n % 2 == i % 2) {
                a[last++] = a[i];
            }
        }

        for (size_t i = 0; i <= k; ++i) {
            neg_c[i] = (i % 2 == 0 ? c[i] : mod(-c[i]));
        }
        for (size_t i = 0; i <= (k << 1); i += 2) {
            long long r = 0;
            for (size_t j = 0; j <= i; ++j) {
                if (i - j > k || j > k) continue;
                r = mod(r + mod(c[j] * neg_c[i - j]));
            }
            R[i/2] = r;
        }

        for (size_t i = 0; i <= k; ++i) {
            c[i] = R[i];
        }


        n = (n >> 1);
    }
    std::cout << a[n];
}
