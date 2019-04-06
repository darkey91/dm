#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>

void parseString(std::vector<std::vector<bool>> &g, int v, const std::string &s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            g[v][i] = true;
            g[i][v] = true;
        }
    }
}

int main() {
    FILE *in = fopen("chvatal.in", "r");
    FILE *out = fopen("chvatal.out", "w");
    int n, begin = 0;
    fscanf(in, "%d", &n);

    char s[4005];
    std::vector<std::vector<bool>> g(n, std::vector<bool>(n, false));

    std::vector<int> q;
    q.push_back(0);

    for (int i = 1; i < n; ++i) {
        fscanf(in, "%s", s);
        parseString(g, i, s);
        q.push_back(i);
    }

    for (int i = 0; i < n * (n - 1); ++i) {
        if (!g[q[begin]][q[begin + 1]]) {
            int j = begin + 2;
            while (j != q.size() - 1 && (!g[q[begin]][q[j]] || !g[q[begin + 1]][q[j + 1]])) {
                ++j;
            }
            if (j == q.size() - 1) {
                int k = begin + 2;
                while (k < q.size() && !g[q[begin]][q[k]])
                    ++k;
                std::reverse(q.begin() + begin + 1, q.begin() + k + 1);

            } else {
                std::reverse(q.begin() + begin + 1, q.begin() + j + 1);
            }
        }
        q.push_back(q[begin++]);
    }

    for (;begin < q.size(); ++begin) {
        fprintf(out, "%i ", q[begin] + 1 );
    }

    return 0;
}