#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream in("check.in");
    std::ofstream out("check.out");

    size_t n, m, size;
    in >> n >> m;
    int maxSize = (1 << n);

    bool first = false, sec = true;

    std::set<int> S;
    std::set<std::pair<int, int>> sets;

    for (size_t i = 0; i < m; ++i) {
        in >> size;
        if (size == 0) {
            first = true;
            continue;
        }

        int little_set = 0, element;
        for (size_t j = 0; j < size; ++j) {
            in >> element;
            --element;
            little_set |= (1 << element);
        }
        sets.insert(std::make_pair(size, little_set));
        S.insert(little_set);

    }


    std::vector<bool> second(maxSize, false);
    second[0] = true;
    for (int i = 1; i < maxSize; ++i) {
        if (S.find(i) != S.end()) {
            second[i] = true;
            for (int without = 0;(1 << without) <= i ; ++without) {
                if (((1 << without) & i) != 0) {
                    int temp = ~(1 << without);
                    int setForCheck = i & temp;
                    second[i] = second[i] & second[setForCheck];
                }
            }

        }
    }

    for (auto s: S) {
        if (!second[s]) {
            sec = false;
            break;
        }
    }

    if (!first || !sec) {
        out << "NO";
        return 0;
    }


    for (auto it = sets.begin(); it != sets.end(); ++it) {
        for (auto jt = it; jt != sets.end(); ++jt) { // jt > it
            bool third = false;
            if ((it->second | jt->second) == jt->second) { // it - subset of jt
                continue;
            }
            if (jt->first > it->first) {
                int difference = jt->second & (it->second ^ jt->second);

                for (int x = 0; (1 << x) <= difference; ++x) {
                    if ((difference & (1 << x)) != 0) {
                        int b_union_x = (1 << x) | it->second;
                        if (S.find(b_union_x) != S.end()) {
                            third = true;
                            break;
                        }
                    }
                }

                if (!third) {
                    out << "NO";
                    return 0;
                }
            }

        }

    }


    out << "YES";
    return 0;
}