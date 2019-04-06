#include <algorithm>
#include <string>
#include <vector>

void parseString(std::vector<std::vector<bool>> &g, int v, const std::string &s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            g[v][i] = true;
            g[i][v] = true;
        }
    }
}


int main() {
    FILE *out = fopen("fullham.out", "w");
    FILE *in = fopen("fullham.in", "r");

    int n, begin = 0, end;
    fscanf(in, "%i", &n);


    std::vector<std::vector<bool>> g(n, std::vector<bool>(n, false));
    char s[4005];
    std::vector<int> q;

    q.push_back(0);

    for (int i = 1; i < n; ++i) {
        fscanf(in, "%s", s);
        parseString(g, i, s);
        q.push_back(i);
    }

    for (int i = 0; i <= (n << 1); ++i) {
        if (!g[q[begin]][q[begin + 1]]) {
            int j = begin + 2;
            while (!g[q[begin]][q[j]] || !g[q[begin + 1]][q[j + 1]])
                ++j;
            std::reverse(q.begin() + begin + 1, q.begin() + j + 1);
        }
        q.push_back(q[begin]);
        ++begin;
    }


    for (; begin < q.size(); ++begin) {
        fprintf(out, "%i ", q[begin] + 1);
    }


    return 0;
}