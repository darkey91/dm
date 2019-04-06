#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

class Automata {
    int n = 30;
    vector<set<char>> tr;
    char start;

public :
    bool eps[101] = {false};

    set<char> epsState;

    Automata() {
        tr.resize(n);
    }

    void checkEps() {
        bool isChanged = false;
        do {
            for (int i = 0; i < 'Z' - 'A' + 1; ++i) {
                if (epsState.count(i + 'A') == 0 && isEachToEps(i + 'A')) {
                    epsState.insert(i + 'A');
                    isChanged = true;
                    break;
                } else isChanged = false;
            }
        } while (isChanged);
    }

    bool isEachToEps(char v) {
        for (auto to: tr[v - 'A']) {
            if (to > 'Z' || epsState.count(to) == 0) {
                return false;
            }
        }
        return !tr[v - 'A'].empty();
    }

    void addTransition(char from, char to) {
        tr[from - 'A'].insert(to);
    }

    void setStart(char s) {
        this->start = s;
    }
};

int main() {
    ifstream in("epsilon.in");
    ofstream out("epsilon.out");
    char start, left;
    int n;
    in >> n >> start;
    Automata a;
    a.setStart(start);
    string tmp;

    for (int i = 0; i < n; ++i) {
        in >> left;
        getline(in, tmp);
        if (tmp.length() == 3) {
            a.eps[left - 'A'] = true;
            a.epsState.insert(left);
        } else
            for (int j = 0; j < tmp.size(); ++j) {
                if (tmp[j] >= 'A' && tmp[j] <= 'Z') {
                    a.addTransition(left, tmp[j]);
                }
                if (tmp[j] >= 'a' && tmp[j] <= 'z') {
                    a.addTransition(left, tmp[j]);
                }
            }
    }

    a.checkEps();

    for (auto t: a.epsState) {
        out << t << " ";
    }

    return 0;
}