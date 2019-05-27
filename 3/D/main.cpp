#include <iostream>
#include <fstream>
#include <vector>

uint64_t const MOD = 1000000007;

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("nfc.in");
    out.open("nfc.out");
    size_t n;
    char s;
    in >> n >> s;
    std::vector<std::vector<std::pair<char, char> > > g(26);
    for (size_t i = 0; i < n; i++) {
        char S;
        in >> S;
        std::string enter;
        in >> enter >> enter;
        if (enter.length() == 1) {
            g[S - 'A'].emplace_back(enter[0], 255);
        } else {
            g[S - 'A'].emplace_back(enter[0], enter[1]);
        }
    }
    std::string w;
    in >> w;
    size_t m = w.length();
    std::vector<std::vector<std::vector<uint64_t>>> dp(26,
                                                       std::vector<std::vector<uint64_t>>(m,
                                                                                          std::vector<uint64_t>(m, 0)));
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < 26; j++) {
            for (auto &v : g[j]) {
                if (v.first == w[i] && v.second == static_cast<char>(255)) {
                    dp[j][i][i]++;
                }
            }
        }
    }
    for (size_t l = 1; l < m; l++) {
        for (size_t i = 0; i + l < m; i++) {
            size_t j = i + l;
            for (size_t k = i; k < j; k++) {
                for (size_t p = 0; p < 26; p++) {
                    for (auto &v : g[p]) {
                        if (v.second != static_cast<char>(255)) {
                            dp[p][i][j] =
                                    (dp[p][i][j] + (dp[v.first - 'A'][i][k] * dp[v.second - 'A'][k + 1][j])) % MOD;
                        }
                    }
                }
            }
        }
    }
    uint64_t sum = 0;
    out << dp[s - 'A'][0][m - 1] << std::endl;
    in.close();
    out.close();
    return 0;
}