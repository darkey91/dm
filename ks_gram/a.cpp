#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Automata {
    char traveler;
    bool isTranHere[101][26] = {false};
    std::map<std::pair<char, char>, vector<char>> transitions;
    string w;
    bool ac = false;

    void dfs(pair<char, char> v, int len) {
        if (len == w.size() + 1) {
            ac = ac || (v.first == termState);
            return;
        }

        if (transitions.count(v) > 0) {
            vector<char> tmp = transitions[v];
            for (auto to : tmp) {
                dfs(make_pair(to, w[len]), len + 1);
            }
        }
    }


public:
    char termState = '+';

    void addTransition(char from, char sym, char to) {
        if (isTranHere[from - 'A'][sym - 'a']) {
            transitions.find(make_pair(from, sym))->second.push_back(to);
        } else {
            isTranHere[from - 'A'][sym - 'a'] = true;
            vector<char> tmp;
            tmp.push_back(to);
            transitions.insert(make_pair(make_pair(from, sym), tmp));
        }
    }

    bool isAccepted(const std::string &s) {
        this->w = s;
        ac = false;
        dfs(make_pair(traveler, w[0]), 1);
        return ac;

    }

    void set_start(char s) {
        this->traveler = s;
    }
};


int main() {
    ifstream in("automaton.in");
    ofstream out("automaton.out");
    char start;
    int n;
    in >> n >> start;
    Automata a;
    a.set_start(start);
    string tmp;
    for (int i = 0; i < n; ++i) {
        in >> start;
        getline(in, tmp);
        if (tmp.length() == 6) {
            a.addTransition(start, tmp[4], tmp[5]);
        } else {
            a.addTransition(start, tmp[4], a.termState);
        }
    }
    int m;
    in >> m;
    for (int i = 0; i < m; ++i) {
        in >> start;
        getline(in, tmp);
        if (a.isAccepted(start + tmp)) out << "yes\n";
        else out << "no\n";
    }
    return 0;
}