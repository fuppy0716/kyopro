// https://trap.jp/post/1702/
// 部分木と、その部分木の根の親から根への辺（部分木の親辺）は一対一に対応する（全体の根は除く）
// V: 部分木に対する答えの型
// E: 「部分木 + 部分木の親辺」に対する答えの型
// merge: 「部分木 + 親辺」の答え同士をマージする関数
// e: 「部分木 + 親辺」の答えの単位元
// put_edge: 部分木の答えに、親辺をマージして「部分木 + 部分木の親辺」に対する答えを作る関数
// put_vertex: 自分の子の「部分木 + 親辺」を全てマージしたものに対して、自分の頂点を追加して部分木に対する答えを作る関数
// https://atcoder.jp/contests/dp/submissions/49819731 の提出例も参照
// https://judge.yosupo.jp/submission/187265 の提出例も参照
template <class E, class V, E (*merge)(E, E), E (*e)(), E (*put_edge)(V, int), V (*put_vertex)(E, int)>
struct RerootingDP {
    struct edge {
        int to, idx, xdi;
    };
    RerootingDP(int n_ = 0) : n(n_), inner_edge_id(0) {
        es.resize(2 * n - 2);
        start.resize(2 * n - 2);
        if (n == 1) es_build();
    }
    void add_edge(int u, int v, int idx, int xdi) {
        start[inner_edge_id] = u;
        es[inner_edge_id] = {v, idx, xdi};
        inner_edge_id++;
        start[inner_edge_id] = v;
        es[inner_edge_id] = {u, xdi, idx};
        inner_edge_id++;
        if (inner_edge_id == 2 * n - 2) {
            es_build();
        }
    }
    vector<V> build(int root_ = 0) {
        root = root_;
        vector<V> subdp(n);
        subdp[0] = put_vertex(e(), 0);
        outs.resize(n);
        vector<int> geta(n + 1, 0);
        for (int i = 0; i < n; i++)
            geta[i + 1] = start[i + 1] - start[i] - 1;
        geta[root + 1]++;
        for (int i = 0; i < n; i++)
            geta[i + 1] += geta[i];
        auto dfs = [&](auto sfs, int v, int f) -> void {
            E val = e();
            for (int i = start[v]; i < start[v + 1]; i++) {
                if (es[i].to == f) {
                    swap(es[start[v + 1] - 1], es[i]);
                }
                if (es[i].to == f) continue;
                sfs(sfs, es[i].to, v);
                E nval = put_edge(subdp[es[i].to], es[i].idx);
                outs[geta[v]++] = nval;
                val = merge(val, nval);
            }
            subdp[v] = put_vertex(val, v);
        };
        dfs(dfs, root, -1);
        return subdp;
    }
    vector<V> reroot() {
        vector<E> reverse_edge(n);
        reverse_edge[root] = e();
        vector<V> answers(n);
        auto dfs = [&](auto sfs, int v) -> void {
            int le = outs_start(v);
            int ri = outs_start(v + 1);
            int siz = ri - le;
            vector<E> rui(siz + 1);
            rui[siz] = e();
            for (int i = siz - 1; i >= 0; i--) {
                rui[i] = merge(outs[le + i], rui[i + 1]);
            }
            answers[v] = put_vertex(merge(rui[0], reverse_edge[v]), v);
            E lui = e();
            for (int i = 0; i < siz; i++) {
                V rdp = put_vertex(merge(merge(lui, rui[i + 1]), reverse_edge[v]), v);
                reverse_edge[es[start[v] + i].to] = put_edge(rdp, es[start[v] + i].xdi);
                lui = merge(lui, outs[le + i]);
                sfs(sfs, es[start[v] + i].to);
            }
        };
        dfs(dfs, root);
        return answers;
    }

  private:
    int n, root, inner_edge_id;
    vector<E> outs;
    vector<edge> es;
    vector<int> start;
    int outs_start(int v) {
        int res = start[v] - v;
        if (root < v) res++;
        return res;
    }
    void es_build() {
        vector<edge> nes(2 * n - 2);
        vector<int> nstart(n + 2, 0);
        for (int i = 0; i < 2 * n - 2; i++)
            nstart[start[i] + 2]++;
        for (int i = 0; i < n; i++)
            nstart[i + 1] += nstart[i];
        for (int i = 0; i < 2 * n - 2; i++)
            nes[nstart[start[i] + 1]++] = es[i];
        swap(es, nes);
        swap(start, nstart);
    }
};
