#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in;
    std::ofstream out;
    in.open("problem2.in");
    out.open("problem2.out");
    std::string str;
    in >> str;
    size_t n, m, k;
    in >> n >> m >> k;
    std::vector<size_t> end(k);
    for (size_t i = 0; i < k; i++) {
        size_t number;
        in >> number;
        end[i] = --number;
    }
    std::vector<std::vector<std::vector<bool> > > v(n,
                                                    std::vector<std::vector<bool> >(n, std::vector<bool>(26, false)));
    for (size_t i = 0; i < m; i++) {
        size_t from, to;
        char c;
        in >> from >> to >> c;
        v[--from][--to][c - 'a'] = true;
    }
    std::vector<std::vector<bool> > dp(str.length() + 1, std::vector<bool>(n, false));
    dp[0][0] = true;
    std::queue<std::pair<size_t, size_t> > q;
    q.push(std::make_pair(0, 0));
    bool find = false;
    while (!q.empty()) {
        size_t len = q.front().first,
                u = q.front().second;
        q.pop();
        if (len < str.length()) {
            for (size_t i = 0; i < n; i++) {
                if (v[u][i][str[len] - 'a']) {
                    if (!dp[len + 1][i]) {
                        dp[len + 1][i] = true;
                        q.push(std::make_pair(len + 1, i));
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < end.size(); i++) {
        if (dp[str.length()][end[i]]) {
            find = true;
        }
    }
    out << (find ? "Accepts" : "Rejects") << std::endl;
    in.close();
    out.close();
    return 0;
}
