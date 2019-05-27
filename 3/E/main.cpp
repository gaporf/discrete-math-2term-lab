#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("cf.in");
    out.open("cf.out");
    size_t n;
    char s;
    in >> n >> s;
    std::string str;
    std::getline(in, str);
    std::vector<std::vector<std::string> > g(26);
    for (size_t i = 0; i < n; i++) {
        std::getline(in, str);
        if (str.length() < 6) {
            g[str[0] - 'A'].push_back("");
        } else {
            g[str[0] - 'A'].push_back(str.substr(5));
        }
    }
    std::string w;
    in >> w;
    size_t m = w.length();
    std::vector<std::vector<std::vector<bool> > > a(26, std::vector<std::vector<bool> >(m + 1, std::vector<bool>(m + 1,
                                                                                                                 false)));
    std::vector<std::vector<std::vector<std::vector<std::vector<bool>>>>> h(26);
    for (size_t i = 0; i <= m; i++) {
        for (size_t p = 0; p < 26; p++) {
            for (auto &v : g[p]) {
                if (v.length() == 0) {
                    a[p][i][i] = true;
                } else if (v.length() == 1 && v[0] >= 'a' && v[0] <= 'z' && i < m && v[0] == w[i]) {
                    a[p][i][i + 1] = true;
                }
            }
        }
    }
    for (size_t p = 0; p < 26; p++) {
        h[p].resize(g[p].size(),
                    std::vector<std::vector<std::vector<bool>>>(m + 1, std::vector<std::vector<bool>>(m + 1)));
        for (size_t l = 0; l < g[p].size(); l++) {
            for (size_t i = 0; i <= m; i++) {
                for (size_t j = 0; j <= m; j++) {
                    h[p][l][i][j].resize(g[p][l].size() + 1, false);
                    h[p][l][i][i][0] = true;
                }
            }
        }
    }
    for (size_t l = 0; l <= m; l++) {
        for (size_t i = 0; i + l < m; i++) {
            for (size_t ww = 0; ww < 26; ww++) {
                bool yes = false;
                size_t j = i + l;
                for (size_t p = 0; p < 26; p++) {
                    for (size_t q = 0; q < g[p].size(); q++) {
                        for (size_t b = 0; b < g[p][q].size(); b++) {
                            if (g[p][q][b] >= 'a' && g[p][q][b] <= 'z') {
                                if (w[j] == g[p][q][b] && h[p][q][i][j][b]) {
                                    h[p][q][i][j + 1][b + 1] = true;
                                }
                            } else {
                                for (size_t c = i; c <= j + 1; c++) {
                                    if (h[p][q][i][c][b] && a[g[p][q][b] - 'A'][c][j + 1]) {
                                        h[p][q][i][j + 1][b + 1] = true;
                                    }
                                }
                            }
                        }
                    }
                }
                for (size_t p = 0; p < 26; p++) {
                    for (size_t q = 0; q < g[p].size(); q++) {
                        if (h[p][q][i][j + 1].back() && !a[p][i][j + 1]) {
                            a[p][i][j + 1] = true;
                            yes = true;
                        }
                    }
                }
                if (!yes) {
                    break;
                }
            }
        }
    }
    out << (a[s - 'A'][0][m] ? "yes" : "no") << std::endl;
    in.close();
    out.close();
    return 0;
}