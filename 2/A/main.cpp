#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

void finish(bool mode, std::ifstream &in, std::ofstream &out) {
    out << (mode ? "Accepts" : "Rejects") << std::endl;
    in.close();
    out.close();
    exit(0);
}

int32_t main() {
    std::ifstream in;
    std::ofstream out;
    in.open("problem1.in");
    out.open("problem1.out");
    std::ios_base::sync_with_stdio(false);
    std::string str;
    in >> str;
    size_t n, m, k;
    in >> n >> m >> k;
    std::vector<bool> v(n, false);
    for (size_t i = 0; i < k; i++) {
        size_t num;
        in >> num;
        v[--num] = true;
    }
    std::map<char, size_t> mp[n];
    for (size_t i = 0; i < m; i++) {
        size_t from, to;
        char c;
        in >> from >> to >> c;
        --from;
        --to;
        mp[from][c] = to;
    }
    size_t u = 0;
    for (char c : str) {
        if (mp[u].find(c) != mp[u].end()) {
            u = mp[u][c];
        } else {
            finish(false, in, out);
        }
    }
    finish(v[u], in, out);
    return 0;
}