#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>

uint32_t const MOD = 1000000007;

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("problem5.in");
    out.open("problem5.out");
    size_t n, m, k, l;
    in >> n >> m >> k >> l;
    std::vector<size_t> terminal(n, false);
    for (size_t i = 0; i < k; i++) {
        size_t num;
        in >> num;
        --num;
        terminal[num] = true;
    }
    std::vector<std::vector<std::vector<size_t> > > g(n, std::vector<std::vector<size_t> >(26));
    for (size_t i = 0; i < m; i++) {
        size_t from, to;
        char c;
        in >> from >> to >> c;
        --from;
        --to;
        g[from][c - 'a'].push_back(to);
    }
    std::map<std::set<size_t>, size_t> new_num;
    std::queue<std::set<size_t> > q;
    std::set<size_t> st;
    st.insert(0);
    q.push(st);
    new_num[st] = 0;
    size_t cnt = 1;
    std::vector<std::vector<size_t> > new_g(1, std::vector<size_t>());
    std::vector<bool> new_terminal(1, terminal[0]);
    while (!q.empty()) {
        auto cur = q.front();
        auto cur_num = new_num[cur];
        q.pop();
        for (size_t c = 0; c < 26; c++) {
            std::set<size_t> new_cur;
            bool term = false;
            for (auto i : cur) {
                for (auto to : g[i][c]) {
                    new_cur.insert(to);
                    term |= terminal[to];
                }
            }
            if (new_cur.empty()) {
                continue;
            }
            if (new_num.find(new_cur) == new_num.end()) {
                new_num[new_cur] = cnt++;
                new_g.emplace_back();
                new_terminal.push_back(term);
                q.push(new_cur);
            }
            new_g[new_num[cur]].push_back(new_num[new_cur]);
        }
    }
    std::vector<std::vector<uint32_t> > dp(2, std::vector<uint32_t>(cnt, 0));
    dp[0][0] = 1;
    for (size_t i = 1; i <= l; i++) {
        dp[i % 2].assign(cnt, 0);
        for (size_t from = 0; from < cnt; from++) {
            for (size_t j = 0; j < new_g[from].size(); j++) {
                size_t to = new_g[from][j];
                dp[i % 2][to] = (dp[i % 2][to] + dp[(i - 1) % 2][from]) % MOD;
            }
        }
    }
    uint32_t ans = 0;
    for (size_t i = 0; i < cnt; i++) {
        if (new_terminal[i]) {
            ans = (ans + dp[l % 2][i]) % MOD;
        }
    }
    out << ans << std::endl;
    in.close();
    out.close();
    return 0;
}