#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

struct automate {
    automate(size_t n, size_t m, size_t k, std::ifstream &in) : n(n), m(m), k(k), terminal(n, false), mp(n) {
        for (size_t i = 0; i < k; i++) {
            size_t number;
            in >> number;
            terminal[--number] = true;
        }
        for (size_t i = 0; i < m; i++) {
            size_t from, to;
            char c;
            in >> from >> to >> c;
            --from;
            --to;
            mp[from][c] = to;
        }
    }

    size_t n, m, k;
    std::vector<bool> terminal;
    std::vector<std::map<char, size_t> > mp;
};

bool dfs(automate &first, size_t v, automate &second, size_t u, std::vector<bool> &used) {
    used[v] = true;
    if (first.terminal[v] != second.terminal[u]) {
        return false;
    }
    bool res = true;
    for (char c = 'a'; c <= 'z'; c++) {
        bool a = first.mp[v].find(c) == first.mp[v].end(),
            b = second.mp[u].find(c) == second.mp[u].end();
        if (a != b) {
            return false;
        } else if (a && !used[first.mp[v][c]]) {
            res &= dfs(first, first.mp[v][c], second, second.mp[u][c], used);
        }
    }
    return res;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("isomorphism.in");
    out.open("isomorphism.out");
    size_t n, m, k;
    in >> n >> m >> k;
    automate first(n, m, k, in);
    size_t N, M, K;
    in >> N >> M >> K;
    automate second(N, M, K, in);
    std::vector<bool> used(n, false);
    out << (dfs(first, 0, second, 0, used) ? "YES" : "NO") << std::endl;
    in.close();
    out.close();
    return 0;
}