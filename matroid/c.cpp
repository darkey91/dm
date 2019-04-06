#include <fstream>
#include <vector>
#include <algorithm>

bool dfs(int v, std::vector<bool> &used, const std::vector<std::vector<int>> &g, std::vector<int> &M) {
    if (used[v]) return false;

    used[v] = true;
    for (auto u: g[v]) {
        if (M[u] == -1 || dfs(M[u], used, g, M)) {
            M[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream in("matching.in");
    std::ofstream out("matching.out");

    int n;
    in >> n;
    std::vector<std::pair<int, int>> left(n, std::make_pair(0,0));
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        left[i].first = i;
        in >> left[i].second;
    }

    sort(left.begin(), left.end(), [] (const auto &a, const auto &b) -> bool {
        return b.second < a.second;
    });

    int u, number;
    for (int i = 0; i < n; ++i) {
        in >> number;
        for (int j = 0; j < number; ++j) {
            in >> u;
            --u;
            g[i].push_back(u);
        }
    }

    std::vector<int> M(n, -1);
    std::vector<bool> used;

    for (auto &l: left) {
        used.assign(n, false);
        dfs(l.first, used, g, M);
    }

    std::vector<int> ans(n, 0);

   for (int i = 0; i < n; ++i) {
        if (M[i] != -1) {
            ans[M[i]] = i + 1;
        }
    }

    for (int a: ans) {
        out << a << " ";
    }

    return 0;
}