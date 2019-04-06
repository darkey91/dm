#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <iostream>
using std::vector;

class Automata {
    int traveler = 1;
    std::map<std::pair<int, char>, int> transitions;
    std::set<int> termStates;

    int transit(char sym) {
        std::pair<int, char> transition = std::make_pair(traveler, sym);

        if (transitions.count(transition) > 0) {
            return traveler = transitions.find(transition)->second;
        } else {
            return traveler = -1;
        }
    }

public:
    void addTransition(int from, int to, char sym) {
        transitions.insert(std::make_pair(std::make_pair(from, sym), to));
    }
    void addTermStates(int i) {
        termStates.insert(i);
    }
    bool isAccepted(const std::string &s) {
        for (char i : s) {
            transit(i);
            if (traveler == -1) return false;
        }
        return termStates.count(traveler) > 0;
    }
};


int main() {
    std::ifstream in("problem1.in");
    std::ofstream out("problem1.out");
    std::string s;
    in >> s;
    int n, m, k, letters = 0;
    in >> n >> m >> k;
    Automata a;
    for (int i = 0; i < k; ++i) {
        int t;
        in >> t;
        a.addTermStates(t);
    }

    for (int i = 0; i < m; ++i) {
        int q, w;
        char c;
        in >> q >> w >> c;
        a.addTransition(q, w, c);
        letters = letters | (1 << (c - 'a'));
    }

    if (a.isAccepted(s)) {
        out << "Accepts\n";
    } else {
        out << "Rejects\n";
    }
    return 0;
}