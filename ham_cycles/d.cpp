#include <list>
#include <fstream>
#include <vector>

void parseString(std::vector<std::vector<bool>> &g, int v, const std::string &s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            g[v][i] = true;
        } else if (s[i] == '0') {
            g[i][v] = true;
        }
    }
}


int main() {
    std::ifstream in("guyaury.in");
    std::ofstream out("guyaury.out");

    int n;
    in >> n;
    std::string s;

    std::vector<std::vector<bool>> g(n, std::vector<bool>(n, false));

    for (int i = 1; i < n; ++i) {
        in >> s;
        parseString(g, i, s);
    }

    std::list<int> p, c;
    p.push_back(0);

    for (int i = 1; i < n; ++i) {
        auto it = p.begin();
        while (it != p.end() && g[*it][i]) {
            ++it;
        }
        p.insert(it, i);
    }


    if (g[p.back()][p.front()]) {
        for (auto i: p) {
            out << i + 1 << " ";
        }
        return 0;
    }


    auto third = p.begin();
    std::advance(third, 2);
    auto it = p.end();

    while (it != third ) {
        if (it != p.end() && g[*it][p.front()]) {
            break;
        }
            --it;
    }
    ++it;

    c.insert(c.begin(), p.begin(), it);
    p.erase(p.begin(), it);

    auto ut = p.begin();

    while (c.size() != n ) {
        auto iter = c.begin();
        while (iter != c.end() && g[*iter][*ut]) {
            ++iter;
        }
        ++ut;

        if (iter != c.end()) {
            c.insert(iter, p.begin(), ut);
            p.erase(p.begin(), ut);
            ut = p.begin();
        }

    }

    for (auto i: c) {
        out << i + 1 << " ";
    }

    return 0;
}