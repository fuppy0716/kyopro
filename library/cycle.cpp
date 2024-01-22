// https://judge.yosupo.jp/submission/185433
vector<int> find_cycle_for_directed_graph(const vector<vector<int>> &G) {
    // 有向グラフのサイクルを一つ見つける。見つけたら頂点列を、見つからなかったら空の配列を返す。
    int n = G.size();

    auto dfs = [&](auto &&dfs, int now, vector<int> &used, vector<int> &path) -> int {
        used[now] = 1;
        path.push_back(now);
        for (int ch : G[now]) {
            if (used[ch] == 1) {
                // ch から始まるサイクルを見つけた
                return ch;
            } else if (used[ch] == 0) {
                int res = dfs(dfs, ch, used, path);
                if (res != -1) return res;
            }
        }
        path.pop_back();
        used[now] = 2;
        return -1;
    };

    vector<int> used(n, 0);
    rep(s, n) {
        vector<int> path;
        if (used[s] != 0) continue;
        int ret = dfs(dfs, s, used, path);
        if (ret != -1) {
            rep(i, path.size()) {
                if (path[i] == ret) {
                    return vector<int>(path.begin() + i, path.end());
                }
            }
        }
    }
    return vector<int>();
}

// https://judge.yosupo.jp/submission/185435
vector<int> find_cycle_for_undirected_graph(const vector<vector<int>> &G) {
    // 無向グラフのサイクルを一つ見つける。見つけたら頂点列を、見つからなかったら空の配列を返す。
    int n = G.size();

    // 辺に順番をつけて、同じ頂点対を結ぶ辺を見分ける
    vector<vector<pii>> G2(n);
    int cnt = 0;
    rep(i, n) {
        for (int ch : G[i]) {
            if (i <= ch) {
                G2[i].emplace_back(ch, cnt);
                if (i != ch) {
                    G2[ch].emplace_back(i, cnt);
                }
                cnt++;
            }
        }
    }

    auto dfs = [&](auto &&dfs, int now, int last_edge, vector<int> &used, vector<int> &path) -> int {
        used[now] = 1;
        path.push_back(now);
        for (auto [ch, e] : G2[now]) {
            if (e == last_edge) {
                continue;
            }
            if (used[ch] == 1) {
                // ch から始まるサイクルを見つけた
                return ch;
            } else if (used[ch] == 0) {
                int res = dfs(dfs, ch, e, used, path);
                if (res != -1) return res;
            }
        }
        path.pop_back();
        used[now] = 2;
        return -1;
    };

    vector<int> used(n, 0);
    rep(s, n) {
        vector<int> path;
        if (used[s] != 0) continue;
        int ret = dfs(dfs, s, -1, used, path);
        if (ret != -1) {
            rep(i, path.size()) {
                if (path[i] == ret) {
                    return vector<int>(path.begin() + i, path.end());
                }
            }
        }
    }
    return vector<int>();
}
