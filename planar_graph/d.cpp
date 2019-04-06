#include <fstream>
#include <vector>
#include <cmath>
#include <string>

std::vector<std::vector<size_t>> g;
std::vector<int> color;

void make_g(std::string &d) {
    size_t k = 0;

    for (int i = 0; k < g.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (d[k] == '1') {
                g[i].push_back(j);
                g[j].push_back(i);
            }
            ++k;
        }
    }
}


bool dfs(size_t v, int prev) {
    color[v] = prev == 1 ? 2 : 1;
    for (auto u: g[v]) {
        if (color[u] == 0) {
            return dfs(u, color[v]);
        } else if (u != v && color[u] == color[v]) {
            return false;
        }
    }
    return true;
}

std::vector<int> deg;

bool K5(std::string &s) {
    size_t cnt = 0, knt = 0, k = 0;

    for (int i = 0; k < s.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (s[k] == '1') {
                ++deg[i];
                ++deg[j];
            }
            ++k;
        }
    }
    for (auto d: deg) {
        if (d >= 4) ++cnt;
        if (d >= 3) ++knt;
    }
    return cnt >= 5 || knt >= 6;
}




int m(std::string &s) {
    int e = 0;
    for (auto c: s) {
        if (c == '1') ++e;
    }
    return e;
}

int main() {
    std::ifstream in("planaritycheck.in");
    std::ofstream out("planaritycheck.out");
    size_t t;

   // in >> t;

    std::string s;
    //for (size_t i = 0; i < t; ++i) {
    while(in >> s) {
        in >> s;
        size_t n = (1 + sqrt(1 + 8 * s.size())) / 2;

        if (n < 5) {
            out << "YES\n";
        } else if (n == 5) {
            if (s == "1111111111") out << "NO\n";
            else out << "YES\n";
        } else {
            deg.assign(n, 0);
            if (K5(s)) {
                out << "NO\n";
            } else {
                out << "YES\n";
            }
        }
    }

}