#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

const uint32_t MOD = 1000000007;

void dfs(size_t v, std::vector<std::vector<size_t> > &g, std::vector<bool> &used) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++) {
        size_t to = g[v][i];
        if (!used[to]) {
            dfs(to, g, used);
        }
    }
}

void
bfs(size_t start, size_t n, std::vector<std::vector<size_t> > &g, std::vector<bool> &used, std::vector<bool> &cycle) {
    std::queue<size_t> q;
    std::vector<bool> new_used(n, false);
    dfs(start, g, new_used);
    std::vector<size_t> edge(n, 0);
    for (size_t i = 0; i < n; i++) {
        if (!new_used[i]) {
            continue;
        }
        for (size_t to : g[i]) {
            edge[to]++;
        }
    }
    q.push(start);
    edge[start] = 0;
    while (!q.empty()) {
        size_t v = q.front();
        used[v] = true;
        q.pop();
        for (size_t i = 0; i < g[v].size(); i++) {
            size_t to = g[v][i];
            cycle[to] = cycle[to] | cycle[v];
            edge[to]--;
            if (edge[to] == 0) {
                q.push(to);
            }
        }
    }
}

void dfs1(size_t v, std::vector<std::vector<size_t> > &g, std::vector<bool> &used, std::vector<size_t> &order) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++) {
        size_t to = g[v][i];
        if (!used[to]) {
            dfs1(to, g, used, order);
        }
    }
    order.push_back(v);
}

void dfs2(size_t v, std::vector<std::vector<size_t> > &tr, std::vector<bool> &used, std::vector<size_t> &cl, size_t cur,
          size_t &cnt) {
    used[v] = true;
    cl[v] = cur;
    cnt++;
    for (size_t i = 0; i < tr[v].size(); i++) {
        size_t to = tr[v][i];
        if (!used[to]) {
            dfs2(to, tr, used, cl, cur, cnt);
        }
    }
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in;
    std::ofstream out;
    in.open("problem3.in");
    out.open("problem3.out");
    size_t n, m, k;
    in >> n >> m >> k;
    std::vector<size_t> list_of_term(k);
    for (size_t i = 0; i < k; i++) {
        size_t number;
        in >> number;
        list_of_term[i] = --number;
    }
    std::vector<std::vector<size_t> > g(n), tr(n);
    for (size_t i = 0; i < m; i++) {
        size_t from, to;
        char c;
        in >> from >> to >> c;
        --from;
        --to;
        g[from].push_back(to);
        tr[to].push_back(from);
    }
    std::vector<bool> used(n, false);
    std::vector<size_t> order;
    for (size_t i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i, g, used, order);
        }
    }
    std::reverse(order.begin(), order.end());
    used.assign(n, false);
    size_t cur = 0;
    std::vector<size_t> cl(n);
    std::vector<bool> cycle;
    for (size_t i = 0; i < n; i++) {
        if (!used[order[i]]) {
            size_t cnt = 0;
            dfs2(order[i], tr, used, cl, cur++, cnt);
            cycle.push_back(cnt > 1);
        }
    }
    std::vector<std::vector<size_t> > new_g(cur);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < g[i].size(); j++) {
            size_t from = i,
                    to = g[i][j];
            from = cl[from];
            to = cl[to];
            if (from == to) {
                cycle[from] = true;
            } else {
                new_g[from].push_back(to);
            }
        }
    }
    used.assign(cur, false);
    bfs(cl[0], cur, new_g, used, cycle);
    bool eternal = false;
    for (unsigned long i : list_of_term) {
        if (used[cl[i]] && cycle[cl[i]]) {
            eternal = true;
        }
    }
    if (!eternal) {
        std::vector<size_t> dp(cur, 0);
        std::vector<size_t> edge(cur);
        for (size_t i = 0; i < cur; i++) {
            if (!used[i]) {
                continue;
            }
            for (size_t to : new_g[i]) {
                edge[to]++;
            }
        }
        dp[cl[0]] = 1;
        std::queue<size_t> q;
        q.push(cl[0]);
        while (!q.empty()) {
            size_t v = q.front();
            q.pop();
            for (size_t i = 0; i < new_g[v].size(); i++) {
                size_t to = new_g[v][i];
                dp[to] = (dp[to] + dp[v]) % MOD;
                edge[to]--;
                if (edge[to] == 0) {
                    q.push(to);
                }
            }
        }
        uint32_t ans = 0;
        for (size_t i : list_of_term) {
            ans = (ans + dp[cl[i]]) % MOD;
        }
        out << ans << std::endl;
    } else {
        out << -1 << std::endl;
    }
    in.close();
    out.close();
    return 0;
}