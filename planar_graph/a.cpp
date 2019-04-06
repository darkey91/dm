#include <iostream>
#include <vector>
#include <queue>

struct edge {
    size_t from;
    size_t to;
    edge(size_t to = 0, size_t from = 0) : to(to), from(from) {}
};

bool isIntersection(edge& a, edge& b, const std::vector<size_t> &x) {
    return (x[a.from] < x[b.from] && x[a.to] < x[b.to] && x[a.to] > x[b.from]) || (x[b.from] < x[a.from] && x[b.to] < x[a.to] && x[a.from] < x[b.to]);
}


bool dfs(size_t v, int prev, const std::vector<std::vector<size_t>> &g, std::vector<int> &color) {
    color[v] = prev == 1 ? 2 : 1;
    for (auto u: g[v]) {
        if (color[u] == 0) {
            return dfs(u, color[v], g, color);
        } else if (color[u] == color[v]) {
            return false;
        }
    }
    return true;
}

int main () {
    size_t n, m, u, v;
    edge e;

    std::cin >> n >> m;

    std::vector<edge> edges;

    std::vector<std::vector<size_t>> g(m, std::vector<size_t>());

    for (size_t i = 0; i < m; ++i) {
        std::cin >> e.to >> e.from;
        --e.to; --e.from;
        edges.emplace_back(e);
    }

    std::vector<size_t> x(n, 0);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> u;
        --u;
        x[u] = i;
    }


    for (int i = 0; i < m; ++i) {
        if (edges[i].from > edges[i].to) std::swap(edges[i].from, edges[i].to);
        for (int j = 0; j < m; ++j) {
            if (edges[j].from > edges[j].to) std::swap(edges[j].from, edges[j].to);
            if (i != j && isIntersection(edges[i], edges[j], x)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    std::vector<int> color(m, 0);

    bool f = true;
    for (size_t i = 0; i < m; ++i) {
        if (color[i] == 0) {
            f &= dfs(i, 2, g, color);
        }
    }

    if (f) {
        std::cout << "YES" << std::endl;
        for (size_t i = 0; i < n; ++i) {
            std::cout << x[i] << " " << 0 << " ";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < m; ++i) {
            if (color[i] == 1)
                std::cout << double(x[edges[i].from] + x[edges[i].to]) / 2 << " " << std::max(x[edges[i].to], x[edges[i].from]) - std::min(x[edges[i].to], x[edges[i].from]) << std::endl;
            else if (color[i] == 2) {
                double k =  (std::max(x[edges[i].to], x[edges[i].from]) - std::min(x[edges[i].to], x[edges[i].from]));
                std::cout << double(x[edges[i].from] + x[edges[i].to]) / 2 << " " << k * ( -1) << std::endl;
            }
        }
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}