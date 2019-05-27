#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

std::vector<std::vector<std::vector<size_t> > > inv;
std::vector<std::pair<std::pair<size_t, size_t>, char> > new_g;
std::map<std::pair<std::pair<size_t, size_t>, char>, bool> mp;
std::vector<size_t> terminal;
std::vector<std::vector<std::pair<size_t, char> > > g;
std::vector<std::set<size_t> > p;
std::vector<bool> is_terminal;
std::vector<std::pair<std::pair<size_t, size_t>, char> > ans;

void dfs(size_t v, std::vector<bool> &visit, std::vector<std::vector<std::pair<size_t, char> > > &g) {
    visit[v] = true;
    for (auto u : g[v]) {
        size_t to = u.first;
        if (!visit[to]) {
            dfs(to, visit, g);
        }
    }
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in;
    std::ofstream out;
    in.open("fastminimization.in");
    out.open("fastminimization.out");
    size_t n, m, k;
    in >> n >> m >> k;
    terminal.resize(k);
    for (size_t i = 0; i < k; i++) {
        in >> terminal[i];
        --terminal[i];
    }
    g.resize(n);
    for (size_t i = 0; i < m; i++) {
        size_t from, to;
        char c;
        in >> from >> to >> c;
        --from;
        --to;
        g[from].emplace_back(to, c);
    }
    std::vector<bool> visit(n, false);
    dfs(0, visit, g);
    std::vector<size_t> cl(n, -1);
    size_t cnt = 1;
    for (size_t i = 0; i < n; i++) {
        if (visit[i]) {
            cl[i] = cnt++;
        }
    }
    is_terminal.resize(cnt, false);
    for (size_t i = 0; i < k; i++) {
        size_t v = terminal[i];
        if (visit[v]) {
            is_terminal[cl[v]] = true;
        }
    }
    inv.resize(cnt, std::vector<std::vector<size_t> >(26));
    for (size_t i = 0; i < n; i++) {
        if (!visit[i]) {
            continue;
        }
        size_t v = cl[i];
        std::vector<bool> used(26, false);
        for (auto u : g[i]) {
            size_t to = u.first;
            char c = u.second;
            inv[cl[to]][c - 'a'].push_back(v);
            ans.emplace_back(std::make_pair(v, cl[to]), c);
            used[c - 'a'] = true;
        }
        for (size_t c = 0; c < 26; c++) {
            if (!used[c]) {
                inv[0][c].push_back(v);
            }
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        inv[0][c - 'a'].push_back(0);
    }
    cl.assign(cnt, 1);
    std::set<size_t> term, not_terminal;
    for (size_t i = 0; i < cnt; i++) {
        (is_terminal[i] ? term.insert(i) : not_terminal.insert(i));
        if (is_terminal[i]) {
            cl[i] = 0;
        }
    }
    if (term.empty()) {
        out << "0 0 0";
        out.close();
        in.close();
        return 0;
    }
    p.push_back(term);
    p.push_back(not_terminal);
    std::queue<std::pair<std::set<size_t>, char> > q;
    for (char c = 'a'; c <= 'z'; c++) {
        q.push(std::make_pair(term, c));
        q.push(std::make_pair(not_terminal, c));
    }
    while (!q.empty()) {
        std::set<size_t> C = q.front().first;
        char a = q.front().second - 'a';
        q.pop();
        std::map<size_t, std::set<size_t> > mp;
        for (size_t c : C) {
            for (size_t r : inv[c][a]) {
                size_t i = cl[r];
                if (mp.find(i) == mp.end()) {
                    mp[i] = {};
                }
                mp[i].insert(r);
            }
        }
        for (const auto &i : mp) {
            if (i.second.size() < p[i.first].size()) {
                p.emplace_back();
                size_t j = p.size() - 1;
                for (size_t r : i.second) {
                    p[i.first].erase(r);
                    p[j].insert(r);
                }
                if (p[j].size() > p[i.first].size()) {
                    std::swap(p[i.first], p[j]);
                }
                for (auto r : p[j]) {
                    cl[r] = j;
                }
                for (char c = 'a'; c <= 'z'; c++) {
                    q.push(std::make_pair(p[j], c));
                }
            }
        }
    }
    for (auto it = p.begin(); it != p.end(); it++) {
        if (it->find(0) != it->end()) {
            p.erase(it);
            break;
        }
    }
    if (p.empty()) {
        out << "0 0 0" << std::endl;
        out.close();
        in.close();
        return 0;
    }
    for (size_t i = 0; i < p.size(); i++) {
        if (p[i].find(1) != p[i].end()) {
            swap(p[i], p[0]);
            break;
        }
    }
    std::vector<bool> yes(cnt, false);
    for (size_t i = 0; i < p.size(); i++) {
        for (auto v : p[i]) {
            cl[v] = i;
            yes[v] = true;
        }
    }
    std::vector<size_t> new_terminal;
    for (size_t i = 0; i < p.size(); i++) {
        size_t v = *p[i].begin();
        if (is_terminal[v]) {
            new_terminal.push_back(i + 1);
        }
    }
    for (auto e : ans) {
        size_t v = e.first.first,
                to = e.first.second;
        char c = e.second;
        if (yes[v] && yes[to] && !mp[std::make_pair(std::make_pair(cl[v], cl[to]), c)]) {
            mp[std::make_pair(std::make_pair(cl[v], cl[to]), c)] = true;
            new_g.emplace_back(std::make_pair(cl[v], cl[to]), c);
        }
    }
    out << p.size() << " " << new_g.size() << " " << new_terminal.size() << std::endl;
    for (auto v : new_terminal) {
        out << v << " ";
    }
    out << std::endl;
    for (auto e : new_g) {
        out << e.first.first + 1 << " " << e.first.second + 1 << " " << e.second << std::endl;
    }
    in.close();
    out.close();
    return 0;
}