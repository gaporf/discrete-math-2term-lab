#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <queue>

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("automaton.in");
    out.open("automaton.out");
    std::ios_base::sync_with_stdio(false);
    size_t n;
    char s;
    in >> n >> s;
    std::map<char, std::vector<std::pair<char, char>>> mp;
    for (size_t i = 0; i != n; i++) {
        char S;
        in >> S;
        std::string enter;
        in >> enter >> enter;
        if (enter.length() == 1) {
            mp[S].emplace_back(enter[0], 255);
        } else {
            mp[S].emplace_back(enter[0], enter[1]);
        }
    }
    size_t m;
    in >> m;
    while (m--) {
        std::string word;
        in >> word;
        std::queue<std::pair<size_t, char> > q;
        q.push(std::make_pair(0, s));
        bool yes = false;
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            if (x.first == word.length() && x.second == static_cast<char>(255)) {
                yes = true;
                break;
            }
            auto v = mp[x.second];
            for (auto &i : v) {
                if (i.first == word[x.first]) {
                    q.push(std::make_pair(x.first + 1, i.second));
                }
            }
        }
        out << (yes ? "yes" : "no") << std::endl;
    }
    in.close();
    out.close();
    return 0;
}