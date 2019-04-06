#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef long long lo;

class DSU {
public:
    DSU(size_t n) {
        parents.assign(n, 0);
        rang.assign(n, 0);
        for (size_t i = 0; i < n; ++i) {
            parents[i] = i;
        }
    }

    size_t get(size_t v) {
        return parents[v] = (parents[v] == v) ? v : get(parents[v]);
    }

    void unionSets(size_t u, size_t v) {
        v = get(v);
        u = get(u);

        if (u != v) {
            if (rang[u] > rang[v]) {
                std::swap(u, v);
            }
            parents[u] = v;
            if (rang[v] == rang[u]) ++rang[v];
        }
    }

private:
    std::vector<size_t> parents;
    std::vector<size_t> rang;
};

class edge {
public:
    size_t v, u, number;
    lo w;
    bool removed = true;
    edge(size_t u, size_t v, lo w, size_t number) : number(number), u(u), v(v), w(w) {}
};

int main() {
    std::ifstream in("destroy.in");
    std::ofstream out("destroy.out");

    size_t n, m, u, v, cnt;
    lo s, fine = 0, w;
    in >> n >> m >> s;
    cnt = m - n + 1;

    DSU dsu(n);

    std::vector<edge> edges;

    for (size_t i = 0; i < m; ++i) {
        in >> u >> v >> w;
        --u; --v;
        fine += w;
        edges.emplace_back(edge(u, v, w, i));
    }

    sort(edges.begin(), edges.end(), [] (const edge &a, const edge &b) {
        return a.w > b.w;
    });

    for (auto &e: edges) {
        size_t a = dsu.get(e.u), b = dsu.get(e.v);
        if (b != a) {
            dsu.unionSets(a, b);
            e.removed = false;
            fine -= e.w;
        }
    }

    for (auto &e: edges) {
        if (fine <= s) break;
        if (e.removed) {
            e.removed = false;
            fine -= e.w;
            --cnt;
        }
    }
    sort(edges.begin(), edges.end(), [] (const edge &a, const edge &b) {
        return b.number > a.number;
    });

    out << cnt << std::endl;

    for (auto &e: edges) {
        if (e.removed)
            out << e.number + 1 <<" ";
    }

    return 0;
}