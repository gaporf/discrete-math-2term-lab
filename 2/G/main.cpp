#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>

struct automate {
    explicit automate(std::ifstream &in) {
        in >> n >> m >> k;
        terminal.resize(n, false);
        yes.resize(n, false);
        for (size_t i = 0; i < k; i++) {
            size_t num;
            in >> num;
            --num;
            terminal[num] = true;
            yes[num] = true;
        }
        mp.resize(n);
        for (size_t i = 0; i < m; i++) {
            size_t from, to;
            char c;
            in >> from >> to >> c;
            mp[--from][c] = --to;
        }
    }

    size_t n, m, k;
    std::vector<bool> terminal, yes;
    std::vector<std::map<char, size_t> > mp;
};

void dfs(size_t v, std::vector<std::map<char, size_t> > &mp, std::vector<bool> &terminal, std::vector<bool> &used) {
    used[v] = true;
    for (char c = 'a'; c <= 'z'; c++) {
        if (mp[v].find(c) != mp[v].end()) {
            size_t to = mp[v][c];
            if (!used[to]) {
                dfs(to, mp, terminal, used);
            }
            terminal[v] = terminal[v] | terminal[to];
        }
    }
}

void check(automate &a) {
    std::vector<bool> used(a.n, false);
    dfs(0, a.mp, a.yes, used);
}

bool is_equal(automate &first, automate &second) {
    std::vector<std::vector<bool> > used(first.n, std::vector<bool>(second.n, false));
    std::queue<std::pair<size_t, size_t> > q;
    q.push(std::make_pair(0, 0));
    used[0][0] = true;
    while (!q.empty()) {
        size_t v = q.front().first,
            u = q.front().second;
        if (first.terminal[v] != second.terminal[u]) {
            return false;
        }
        q.pop();
        for (char c = 'a'; c <= 'z'; c++) {
            bool a = (first.mp[v].find(c) != first.mp[v].end()),
                b = (second.mp[u].find(c) != second.mp[u].end());
            if (a && !b) {
                if (first.yes[first.mp[v][c]]) {
                    return false;
                }
            } else if (!a && b) {
                if (second.yes[second.mp[u][c]]) {
                    return false;
                }
            } else if (a && b) {
                size_t V = first.mp[v][c],
                    U = second.mp[u][c];
                if (!used[V][U]) {
                    q.push(std::make_pair(V, U));
                    used[V][U] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("equivalence.in");
    out.open("equivalence.out");
    automate first(in),
            second(in);
    check(first);
    check(second);
    out << (is_equal(first, second) ? "YES" : "NO") << std::endl;
    in.close();
    out.close();
    return 0;
}