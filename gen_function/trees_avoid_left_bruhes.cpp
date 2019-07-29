#include <iostream>
#include <vector>

static const size_t SZ = 5001;
static long long C[SZ][SZ];
static const long long MOD = 998244353;

void comb() {
    for (size_t i = 0; i < SZ; ++i) {
        C[i][0] = C[i][i] = 1;
        for(size_t j = 1; j < i; ++j) {
            C[i][j] = ((C[i - 1][j - 1] + C[i - 1][j] % MOD) + MOD) % MOD;
        }
    }
}

int main() {
    comb();
    size_t n, k;
    std::cin >> k >> n;

    size_t size1 = ((k - 1) >> 1);
    size_t size2 = (k >> 1);

    if (k % 2) {
        ++size2;
    } else {
        ++size1;
    }
    std::vector<long long> v1(SZ, 0), v2(SZ, 0), back(SZ, 0), ans;

    for (size_t i = 0; i < size1; ++i) {
        v1[i] = (i % 2 ? - 1 : 1);
        v1[i] *= C[k - i - 2][i];
    }
    for (size_t i = 0; i < size2; ++i) {
        v2[i] = (i % 2 ? - 1 : 1);
        v2[i] *= C[k - i - 1][i];
    }

    back[0] = (1 / v2[0]);
    size_t last = 0;

    for (size_t i = 1; i <= n; ++i) {
       long long tmp = 0;

       for (size_t j = 1; j <= i; ++j) {
           tmp = (((tmp + v2[j] * back[i - j]) % MOD) + MOD) % MOD;
       }
       back[++last] = (((-tmp / v2[0]) % MOD) + MOD) % MOD;
    }

    for (size_t i = 0; i < n; ++i) {
       long long tmp = 0;

       for (size_t j = 0; j <= i; ++j) {
           tmp = (((tmp + v1[j] * back[i - j]) % MOD) + MOD) % MOD;
       }
       ans.push_back(tmp);
    }

    for (auto a: ans) {
        std::cout << a << "\n";
    }

    return 0;
}
