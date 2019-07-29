#include <iostream>
#include <vector>

int main() {
    size_t n, m;
    long long c, mod = 1e9 + 7.;
    std::cin >> n >> m;
    std::vector< long long>  ans(m + 1, 0), tree(m + 1, 0);
    std::vector<bool> weight(m + 1, false);

    long long min_ = mod;

    for (size_t i = 0; i <  n; ++i) {
        std::cin >> c;
        weight[c] = 1;
        min_ = std::min(min_, c);
    }

    ans[0] = 1;
    ans[min_] = 1;

    tree[0] = 1;
    tree[min_] = 2;

    for (size_t i = min_ + 1; i <= m; ++i) {
        for (size_t w = 1; w <= i; ++w) {
            if (weight[w])
                ans[i] = (ans[i] + tree[i - w]) % mod;
        }

        for (size_t j = 0; j <= i; ++j) {
            tree[i] = (tree[i] + (ans[j] * ans[i - j]) % mod) % mod;
        }
    }
    for (size_t i = 1; i <= m; ++i) {
        std::cout << ans[i] << " ";
    }
    return 0;
}
