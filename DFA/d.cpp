#include <fstream>
#include <vector>

using namespace std;

class dfa {
    int n, mod = int(1e9) + 7;

    vector<vector<long long>> tr, cur, pur, e;
    vector<bool> termState;

    void mult(vector<vector<long long>> &a, vector<vector<long long>> &b) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                pur[i][j] = 0;
                for (int k = 1; k <= n; ++k) {
                    pur[i][j] = (pur[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                a[i][j] = pur[i][j];
            }
        }
    }

    void ppp(int l) {
        while (l) {
            if (l & 1) {
                mult(e, tr);
            }
            mult(tr, tr);
            l >>= 1;
        }
    }


public:

    dfa(int n) {
        this->n = n;
        termState.resize(n + 1, false);
        tr.resize(n + 1);
        cur.resize(n + 1);
        pur.resize(n + 1);
        e.resize(n + 1);

        for (int i = 0; i <= n; ++i) {
            e[i] = vector<long long>(n + 1, 0);

            e[i][i] = 1;
            tr[i] = vector<long long>(n + 1, 0);
            cur[i] = vector<long long>(n + 1, 0);
            pur[i] = vector<long long>(n + 1, 0);
        }
    }


    void addTransition(int from, int to) {
        tr[from][to] += 1;
        cur[from][to] += 1;
    }

    void addTerm(int k) {
        termState[k] = true;
    }

    long long getNumber(int l) {
        ppp(l);

        long long cnt = 0, i = 1;
        for (int j = 1; j <= n; ++j) {
            if (termState[j])
                cnt = (cnt + e[i][j]) % mod;
        }

        return cnt;
    }

};

int main() {
    ifstream in("problem4.in");
    ofstream out("problem4.out");

    int n, m, k, l;
    in >> n >> m >> k >> l;

    dfa a(n);

    for (int i = 0; i < k; ++i) {
        int o;
        in >> o;
        a.addTerm(o);
    }

    for (int i = 0; i < m; ++i) {
        int q, w;
        char e;
        in >> q >> w >> e;
        a.addTransition(q, w);
    }
    out << a.getNumber(l);

    return 0;

}