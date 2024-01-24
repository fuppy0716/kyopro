
vector<mint> hashes;

mint enumerate_triangles(vii G) {
    // グラフ G に存在する三角形（三頂点が互いに隣接している）の個数を数える
    // ただし、MLE の関係で全ての三角形における hash[u] * hash[v] * hash[w] の和を求める
    // see: https://judge.yosupo.jp/submission/185898

    int n = G.size();

    vii G2(n);
    // 次数が小さい方から大きい方への辺のみを貼った有向グラフを作る
    // トポロジカルソートされていることになる
    rep(u, n) {
        for (int v : G[u]) {
            if (pii(G[u].size(), u) < pii(G[v].size(), v)) {
                G2[u].push_back(v);
            }
        }
    }

    // トポロジカルソートされているので三角形は u->v, u->w, v->w のようになる
    // u->v の辺について、u からも v からも辺が出ている頂点 w があるとき三角形 uvw が存在する
    vi exists_edge(n, -1);
    int check_cnt = 0;

    mint ans = 0;
    rep(u, n) {
        for (int v : G2[u]) {
            // u から出ている辺にマーキング
            for (int w : G2[u]) {
                exists_edge[w] = check_cnt;
            }

            // v から出ている辺について、u からも辺が出ている頂点があるか調べる
            for (int w : G2[v]) {
                if (exists_edge[w] == check_cnt) {
                    ans += hashes[u] * hashes[v] * hashes[w];
                }
            }

            check_cnt++;
        }
    }
    return ans;
}
