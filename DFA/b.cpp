#include <string>
#include <fstream>
#include <map>
#include <set>
#include <queue>

using namespace std;

class Automata {
    map<pair<int, char>, vector<int>> transitions;
    bool termStates[101] = {false};
    vector<set<int>> R;
    bool isTranHere[101][26] = {false};

public:
    void addTransition(int from, int to, char sym) {
        if (isTranHere[from][sym - 'a']) {
            transitions.find(make_pair(from, sym))->second.push_back(to);
        } else {
            isTranHere[from][sym - 'a'] = true;
            vector<int> tmp;
            tmp.push_back(to);
            transitions.insert(make_pair(make_pair(from, sym), tmp));
        }
    }

    void addTermStates(int i) {
        termStates[i] = true;
    }

    bool isAccepted(const std::string &s) {
        R.resize(s.length());
        R[0].insert(1);
        for (int i = 1; i < s.length(); ++i) {
           for (auto q : R[i - 1]) {
                if (isTranHere[q][s[i] - 'a']) {
                    vector<int> *state =  &transitions.find(make_pair(q, s[i]))->second;
                    for (int o : *state) {
                        R[i].insert(o);
                    }
                }
            }
        }
        for (auto q: R[s.length() - 1]){
            if (termStates[q]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Automata a;
    ios_base::sync_with_stdio(false);
    ifstream in("problem2.in");
    ofstream out("problem2.out");
    string word = " ", tmp;
    in >> tmp;
    word += tmp;
    int n, m, k;
    in >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int s;
        in >> s;
        a.addTermStates(s);
    }

    for (int i = 0; i < m; ++i) {
        int from, to;
        char c;
        in >> from >> to >> c;
        a.addTransition(from, to, c);
    }

    if (a.isAccepted(word)) {
        out << "Accepts\n";
    } else {
        out << "Rejects\n";
    }

    return 0;

}