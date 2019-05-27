#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

void dfs(char v, std::vector<std::vector<std::string> > &g, std::vector<bool> &visit, std::vector<bool> &useless) {
    visit[v - 'A'] = true;
    for (auto &s : g[v - 'A']) {
        bool go = true;
        for (auto &c : s) {
            if (c >= 'A' && c <= 'Z' && useless[c - 'A']) {
                go = false;
            }
        }
        if (go) {
            for (auto &c : s) {
                if (c >= 'A' && c <= 'Z' && !visit[c - 'A']) {
                    dfs(c, g, visit, useless);
                }
            }
        }
    }
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("useless.in");
    out.open("useless.out");
    size_t n;
    char s;
    in >> n >> s;
    std::vector<std::vector<std::string> > g(26);
    std::string str;
    std::getline(in, str);
    for (size_t i = 0; i < n; i++) {
        std::getline(in, str);
        if (str.length() < 6) {
            g[str[0] - 'A'].push_back("");
        } else {
            g[str[0] - 'A'].push_back(str.substr(5));
        }
    }
    std::vector<bool> mentioned(26, false),
            useless(26, true);
    std::queue<size_t> q;
    mentioned[s - 'A'] = true;
    for (size_t i = 0; i < 26; i++) {
        if (!g[i].empty()) {
            bool add = false;
            mentioned[i] = true;
            for (auto &s : g[i]) {
                bool cur = true;
                for (auto &c : s) {
                    if (c >= 'A' && c <= 'Z') {
                        mentioned[c - 'A'] = true;
                        cur = false;
                    }
                }
                add |= cur;
            }
            if (add) {
                useless[i] = false;
                q.push(i);
            }
        }
    }
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (size_t i = 0; i < 26; i++) {
            if (useless[i] && !g[i].empty()) {
                bool add = false;
                for (auto &s : g[i]) {
                    bool cur = true;
                    for (auto &c : s) {
                        if (c >= 'A' && c <= 'Z' && useless[c - 'A']) {
                            cur = false;
                        }
                    }
                    add |= cur;
                }
                if (add) {
                    useless[i] = false;
                    q.push(i);
                }
            }
        }
    }
    std::vector<bool> visit(26, false);
    if (!useless[s - 'A']) {
        dfs(s, g, visit, useless);
    }
    for (size_t i = 0; i < 26; i++) {
        if (!visit[i]) {
            useless[i] = true;
        }
        if (mentioned[i] && useless[i]) {
            out << static_cast<char>(i + 'A') << " ";
        }
    }
    in.close();
    out.close();
    return 0;
}