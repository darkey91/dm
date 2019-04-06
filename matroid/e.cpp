#include <fstream>
#include <vector>
#include <climits>
#include <set>
#include <map>

int main () {
    std::ifstream in("cycles.in");
    std::ofstream out("cycles.out");

    size_t n, m, elem, weight;
    in >> n >> m;

    std::multimap<int, int, std::greater<>> elements;
    std::vector<bool> S(static_cast<size_t> (1 << n), true);

    for (int i = 0; i < n; ++i) {
        in >> weight;
        elements.insert(std::make_pair(weight, i));
        }

    //generate all depended sets

    size_t size;
    std::set<int> DS;

    for (size_t i = 0; i < m; ++i) {
        in >> size;

        int depended_set = 0;
        for (size_t j = 0; j < size; ++j) {
            in >> elem;
            --elem;
            depended_set = depended_set | (1 << elem);
            }
        S[depended_set] = false;
        DS.insert(depended_set);

        for (size_t x = 0; x < n; ++x) {
            depended_set |= (1 << x);
            S[depended_set] = false;
            }
        }

    size_t base = 0;
    long long result = 0;

    for (auto &e: elements) {
        if (S[base | (1 << e.second)]) {
            base |= (1 << e.second);
            result += e.first;
            }
        }

    out << result;


    return 0;
}