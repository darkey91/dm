#include <iostream>
#include <vector>

static size_t N, M, MAX = 1001;
static const long long MOD =  998244353;

long long mod(long long number) {
    long long m = number % MOD;
    return m < 0 ? m + MOD : m;
}

void multiply(std::vector<long long> &a, std::vector<long long> &b, std::vector<long long> &res, size_t to) {
    for (size_t i = 0; i <= to; ++i) {
        res[i] = 0;
        for (size_t j = 0; j <= i; ++j) {
            res[i] = mod(res[i] + mod(a[j] * b[i - j]));
        }
    }
}

void print(std::vector<long long> &v, size_t to) {
    for (size_t i = 0; i <= to; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cin >> N >> M;
    size_t power = std::max(N, M);

    std::vector<long long> P(MAX + MAX, 0), Q(MAX + MAX, 0), res(MAX + MAX, 0);
    long long x;
    for (size_t i = 0; i <= N; ++i) {
        std::cin >> x;
        P[i] = x;
    }
    for (size_t i = 0; i <= M; ++i) {
        std::cin >> x;
        Q[i] = x;
    }

    for (size_t i = 0; i <= power; ++i) {
          res[i] = mod(P[i] + Q[i]);
    }

    std::cout << power << "\n";
    print(res, power);

    multiply(P, Q, res, N + M);

    std::cout << N +  M << "\n";
    print(res, N + M);

    std::vector<long long> inv_Q(MAX, 0);

    inv_Q[0] = 1 / Q[0];

    for (size_t i = 1; i <= 1000; ++i) {
        for (size_t j = 0; j < i; ++j) {
            inv_Q[i] = mod(inv_Q[i] + mod(inv_Q[j] * Q[i - j]));
        }
        inv_Q[i] = mod(-(inv_Q[i] / inv_Q[0]));

    }

    multiply(P, inv_Q, res, MAX - 2);
    std::cout << "\n";
    print(res, MAX - 2);

    return 0;
}
