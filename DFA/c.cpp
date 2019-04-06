#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

int mod = int(1e9) + 7;

class DFA {
    int n;
    set<int> termStates;
    vector<pair<bool, bool>> isTermAndStart;
    vector<vector<int>> transitions;
    vector<long long> dis;


    vector<set<int>> g, g1;
    vector<char> cl;
    bool ok = true;

    void dfs(int v) {
        cl[v] = 1;
        for (auto it: g1[v]) {
            if (!cl[it]) {
                isTermAndStart[it].second = true;
                dfs(it);
                }
            }
        }

    long long dfs1(int v, int p, long long c) {
        cl[v] = 1;
        dis[v] = 1;
        long long sum = 0;
        for (auto to: g[v]) {
            if (cl[to] != 1) {
                if (isTermAndStart[to].second) {
                    sum = (sum + (transitions[to][v] * dfs1(to, v, c)) % mod) % mod;
                    }

                } else if (cl[to] == 1) {
                ok = false;
                return -1;
                }
            }
        dis[v] = sum;
        if (sum == 0) dis[v] = 1;

        cl[v] = 2;

        return dis[v];
        }


public:
    DFA(int n) {
        this->n = n;
        dis.resize(n + 1, 0);
        transitions.resize(n + 1, vector<int>(n + 1, 0));
        g.resize(n + 1);
        g1.resize(n + 1);
        cl.resize(n + 1, 0);
        isTermAndStart.resize(n + 1, make_pair(false, false));
        }

    void addTransit(int from, int to, char c) {
        ++transitions[from][to];
        g[to].insert(from);
        g1[from].insert(to);
        }

    void addTermState(int i) {
        termStates.insert(i);
        isTermAndStart[i].first = true;
        }

    long long getAmount() {
        long long ans = 0;
        dfs(1);
        isTermAndStart[1].second = true;
        for (auto to: termStates) {
            cl.clear();
            cl.resize(n + 1, 0);
            dfs1(to, 1, 1);
            ans += dis[to] % mod;
            dis.clear();
            dis.resize(n + 1, 0);
            }

        if (!ok) {
            return -1;
            } else {
            return ans;
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    ifstream in("problem3.in");
    ofstream out("problem3.out");

    int n, m, k;
    in >> n >> m >> k;
    DFA a(n);

    for (int i = 0; i < k; ++i) {
        int y;
        in >> y;
        a.addTermState(y);
        }

    for (int i = 0; i < m; ++i) {
        int f, b;
        char c;
        in >> f >> b >> c;
        a.addTransit(f, b, c);
        }

    out << a.getAmount();
    return 0;
}