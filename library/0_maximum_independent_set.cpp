// dp[mask] := mask に含まれる頂点しか使えない時の最大得点
// mask に含まれる頂点を全て使った時の得点ではないことに注意
vl calc_dp(vi a, const vl &score, const vii &out) {
    int n = a.size();
    vl dp(1 << n, -INF);
    dp[0] = 0;
    rep(i, 1 << n) {
        static vi stand, sit;
        stand.clear();
        sit.clear();
        rep(j, n) {
            if (i & (1 << j))
                stand.push_back(j);
            else
                sit.push_back(j);
        }

        for (int j : sit) {
            int ni = i | (1 << j);
            bool ok = true;
            for (int k : stand) {
                if (out[a[j]][a[k]]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                chmax(dp[ni], dp[i] + score[a[j]]);
            } else {
                chmax(dp[ni], dp[i]);
            }
        }
    }
    return dp;
}

// G は辺を表す、score は各頂点を使った時のスコア
// https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/26092906
long long maximum_independent_set(vii G, vl score = vl()) {
    int n = G.size();
    if (score.size() == 0) {
        score.resize(n);
        fill(all(score), 1);
    }

    if (n == 1) return score[0];

    vii out(n, vi(n));
    for (int u = 0; u < n; u++) {
        for (int v : G[u]) {
            out[u][v] = out[v][u] = true;
        }
    }

    int n2 = n / 2;
    vi s1, s2;
    rep(i, n2) {
        s1.push_back(i);
    }
    REP(i, n2, n) {
        s2.push_back(i);
    }

    vl dp1 = calc_dp(s1, score, out), dp2 = calc_dp(s2, score, out);

    ll ans = 0;
    rep(i, dp1.size()) {
        static vi stand;
        stand.clear();
        rep(j, n2) {
            if (i & (1 << j))
                stand.push_back(j);
        }
        int ni = 0;

        for (int u : s2) {
            bool flag = true;
            for (int v : stand) {
                if (out[u][v]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ni |= 1 << (u - n2);
            }
        }

        chmax(ans, dp1[i] + dp2[ni]);
    }
    return ans;
}
