
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>

int main() {
    std::ifstream in("schedule.in");
    std::ofstream out("schedule.out");

    size_t n;
    in >> n;

    long long ans = 0, sum = 0;

    std::vector<std::pair<int, int>> tasks;
    std::set<int, std::greater<>> time;

    int d, w;
    for (int i = 0; i < n; ++i) {
        in >> d >> w;
        sum += w;
        tasks.emplace_back(std::make_pair(d, w));
        time.insert(i + 1);
    }

    std::sort(tasks.begin(), tasks.end(), [] (const auto &a, const auto &b) -> bool {
        return a.second > b.second;
    });

    for (auto &t: tasks) {
        auto free_max_time = time.find(t.first);
        if (free_max_time == time.end())
            free_max_time = time.upper_bound(t.first);
        if (free_max_time != time.end()) {
            time.erase(*free_max_time);
            ans+=t.second;
        } else {
            time.erase(time.begin());
        }
    }
    out << sum - ans;

    return 0;
}