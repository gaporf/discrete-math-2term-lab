#include <iostream>
#include <fstream>
#include <vector>

uint32_t const MOD = 1000000007;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in;
    in.open("problem4.in");
    std::ofstream out;
    out.open("problem4.out");
    size_t n, m, k, l;
    in >> n >> m >> k >> l;
    std::vector<size_t> terminal(k);
    for (size_t i = 0; i < k; i++) {
        in >> terminal[i];
        --terminal[i];
    }
    std::vector<std::pair<size_t, size_t> > g(m);
    for (size_t i = 0; i < m; i++) {
        size_t from, to;
        char c;
        in >> from >> to >> c;
        g[i] = std::make_pair(--from, --to);
    }
    std::vector<std::vector<uint32_t> > dp(2, std::vector<uint32_t>(n, 0));
    dp[0][0] = 1;
    for (size_t i = 1; i <= l; i++) {
        dp[i % 2].assign(n, 0);
        for (size_t j = 0; j < m; j++) {
            size_t from = g[j].first,
                    to = g[j].second;
            dp[i % 2][to] = (dp[i % 2][to] + dp[(i - 1) % 2][from]) % MOD;
        }
    }
    uint32_t ans = 0;
    for (auto v : terminal) {
        ans = (ans + dp[l % 2][v]) % MOD;
    }
    out << ans << std::endl;
    in.close();
    out.close();
    return 0;
}