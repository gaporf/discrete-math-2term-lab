#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void dfs(char v, std::vector<std::vector<std::string>> &g, std::vector<bool> &terminal, std::vector<bool> &used) {
    used[v - 'A'] = true;
    for (auto &i : g[v - 'A']) {
        if (i.empty()) {
            terminal[v - 'A'] = true;
        }
    }
    for (auto &i : g[v - 'A']) {
        bool yes = true;
        for (auto c : i) {
            if (c >= 'a' && c <= 'z') {
                yes = false;
                break;
            } else {
                if (!used[c - 'A']) {
                    dfs(c, g, terminal, used);
                }
                if (!terminal[c - 'A']) {
                    yes = false;
                }
            }
        }
        if (yes) {
            terminal[v - 'A'] = true;
        }
    }
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("epsilon.in");
    out.open("epsilon.out");
    size_t n;
    char s;
    in >> n >> s;
    std::string str;
    std::getline(in, str);
    std::vector<std::vector<std::string> > g(26);
    for (size_t i = 0; i != n; i++) {
        std::getline(in, str);
        if (str.length() < 6) {
            g[str[0] - 'A'].push_back("");
        } else {
            std::string to = str.substr(5);
            g[str[0] - 'A'].push_back(to);
        }
    }
    std::vector<bool> terminal(26, false),
            used(26, false);
    for (size_t i = 0; i < 26; i++) {
        if (!used[i]) {
            dfs((i + 'A'), g, terminal, used);
        }
    }
    for (size_t i = 0; i < 26; i++) {
        if (terminal[i]) {
            out << static_cast<char>('A' + i) << " ";
        }
    }
    in.close();
    out.close();
    return 0;
}