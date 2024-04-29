enum Type { Vertex,
            Compress,
            Rake,
            AddEdge,
            AddVertex };

struct StaticTopTree {
    // https://atcoder.jp/contests/abc351/editorial/9868
    // https://atcoder.jp/contests/abc351/submissions/52777033 を元に、自分好みに書き方を変えたりコメントを追加したり辺クエリに対応したりした
    // 全方位木 DP のライブラリと考え方が似ているのでそちらも参照すると良い

    // G は n 頂点の木を表す連結リストであるとする。
    // 木を HLD のように heavy path と light path に分解する。この時、親からの辺が light edge である頂点と heavy edge である頂点の二種類に分類できる。
    // 前者の頂点を軽頂点、後者の頂点を重頂点と呼ぶ。ただし、根は重頂点であるとする。
    // 頂点も辺も存在しない状態から、以下の操作を行うことで元の木を構築することを考える。この際、頂点が各操作を表すような操作列を表す木も同時に構築する。
    //
    // A-1. 子に軽頂点を持たない頂点を追加する（Vertex）
    // B. 軽頂点が根のクラスタ（部分木的なもの）に親辺を追加する。親頂点は追加しないことに注意（AddEdge）
    // C. 複数の「B. で作られたもの」をマージする（Rake）
    // A-2. 「C. で作られたもの」の親頂点を追加し、「C. で作られたもの」とくっつける（AddVertex）
    // D. 重頂点とその親頂点をマージすることで heavy path を伸ばす（Compress）
    //
    // 実装上は C, D は二つのクラスタのマージを繰り返すことで表現するため、「操作列を表す木」は二分木となる。
    // この際、マージする順番を工夫することで完全二分木に近づけることができ、木の深さを O(log n) に抑えることができる。

    vector<vector<pair<int, int>>> G; // 元のグラフ、(to, edge_idx) のリストで表され、親への辺は含まれない
    int root;                         // 元のグラフでの根
    vector<int> par_edge;             // 元のグラフで各頂点の親への辺のインデックス
    int stt_root;                     // 操作列を表す木の根
    vector<int> P, L, R;              // 操作列を表す木における、親、左の子、右の子
    vector<Type> T;                   // 操作列を表す木における、各頂点の操作タイプ
    vector<int> merged_edge;          // compress / add_edge の操作を表す頂点において、その辺のインデックス
    int add_buf;                      // 操作列を表す木における、新たに追加する頂点のインデックス

    StaticTopTree(const vector<vector<pair<int, int>>> &_G = {}, int _root = 0) : G(_G), root(_root) {
        int n = G.size();
        if (n == 0) {
            return;
        }
        par_edge.resize(n, -1);

        P.resize(4 * n, -1), L.resize(4 * n, -1), R.resize(4 * n, -1);
        T.resize(4 * n, Type::Vertex);
        merged_edge.resize(4 * n, -1);
        add_buf = n;
        build();
    }

    int size() const {
        // 操作列を表す木のサイズを返す
        return add_buf;
    }

  private:
    int dfs(int c, int par = -1) {
        // 部分木のサイズを計算し、最も大きい部分木をリストの先頭に持ってくる
        // また、各頂点の親への辺のインデックスを記録する
        int s = 1, best = 0;
        for (int i = 0; i < (int)G[c].size(); i++) {
            auto [d, ei] = G[c][i];
            par_edge[d] = ei;
            int t = dfs(d, c);
            s += t;
            if (best < t) best = t, swap(G[c][i], G[c][0]);
        }
        return s;
    }
    int add(int k, int l, int r, Type t) {
        if (k == -1) k = add_buf++;
        P[k] = -1, L[k] = l, R[k] = r, T[k] = t;
        if (l != -1) P[l] = k;
        if (r != -1) P[r] = k;
        return k;
    }

    // 以下の pair<int, int> を返す関数は、(操作に対応する頂点のインデックス, 部分木に含まれる実頂点の数) を返す
    // ただし、操作に対応する頂点が作られない場合は (-1, 0) を返す
    pair<int, int> merge(const vector<pair<int, int>> &a, Type t) {
        assert(a.size() > 0);
        if (a.size() == 1) return a[0];
        int u = 0;
        for (auto &[_, s] : a)
            u += s;

        // 二つに振り分けたあとにマージする
        vector<pair<int, int>> b, c;
        for (auto &[i, s] : a)
            (u > s ? b : c).emplace_back(i, s), u -= s * 2;

        auto [i, si] = merge(b, t);
        auto [j, sj] = merge(c, t);

        auto ret = pair<int, int>(add(-1, i, j, t), si + sj);
        if (t == Type::Compress) {
            // compress の操作を表す頂点において、その辺のインデックスを記録する
            // c[0] が今回マージされる子頂点であり、c[0] が Vertex, AddVertex であることは `compress` 関数の仕様から保証される
            merged_edge[ret.first] = par_edge[c[0].first];
        }
        return ret;
    }
    pair<int, int> compress(int i) {
        vector<pair<int, int>> chs;
        while (true) {
            chs.push_back(add_vertex(i));
            if (G[i].size() == 0) {
                break;
            }
            i = G[i][0].first;
        }
        return merge(chs, Type::Compress);
    }
    pair<int, int> rake(int i) {
        vector<pair<int, int>> chs;
        for (int j = 1; j < (int)G[i].size(); j++)
            chs.push_back(add_edge(G[i][j].first));
        return chs.empty() ? make_pair(-1, 0) : merge(chs, Type::Rake);
    }
    pair<int, int> add_edge(int i) {
        // i の親は light path であることが保証される
        auto [j, sj] = compress(i);
        auto ret = pair<int, int>(add(-1, j, -1, Type::AddEdge), sj);
        // add_edge の操作を表す頂点において、その辺のインデックスを記録する
        // i が Vertex, AddVertex であることは `rake` 関数の仕様から保証される
        merged_edge[ret.first] = par_edge[i];
        return ret;
    }
    pair<int, int> add_vertex(int i) {
        auto [j, sj] = rake(i);
        return {add(i, j, -1, j == -1 ? Type::Vertex : Type::AddVertex), sj + 1};
    }
    void build() {
        dfs(root);
        auto [i, n] = compress(root);
        stt_root = i;
    }
};
template <class E, class V>
struct StaticTopTreeDp {
    // static top tree を用いて以下を実現する
    // - 各頂点や辺がある値を持つ木に関する木 DP を行う
    // - 各頂点や辺が持つ値が変わった時に O(log n) で木 DP の値を更新する
    //   - https://atcoder.jp/contests/abc351/submissions/52951833
    //   - https://judge.yosupo.jp/submission/205112
    // - 部分木のサイズ程度の長さの列を値に持つ DP は、分割統治的な考え方で O(n (log n)^2) に高速化できる
    //   - https://atcoder.jp/contests/abc269/submissions/52956082
    //
    // 全方位木 DP のライブラリと考え方が似ているのでそちらも参照すると良い
    // E: クラスタに親辺を追加したもの、それらをマージしたものが持つべき答えの型。AddEdge, Rake に対応。
    // V: 頂点を根に持つクラスタが持つべき答えの型。Vertex, AddVertex, Compress に対応。
    //    ここで、AddVertex と Compress に対応するため、重頂点の子の情報は持たないことに注意。

    StaticTopTree stt;

    function<V(int)> vertex;         // 頂点のインデックス
    function<E(V, int)> add_edge;    // (クラスタの答え, 辺のインデックス)
    function<E(E, E)> rake;          // (マージ対象の左クラスタの答え, 右)
    function<V(E, int)> add_vertex;  // (クラスタの答え, 頂点のインデックス)
    function<V(V, V, int)> compress; // (マージ対象の親クラスタの答え, 子, 辺のインデックス)

    vector<int> child; // 辺ごとに、子の方の頂点を記録する

    vector<E> dp_e; // stt の各頂点に対応するクラスタの答え。頂点が AddEdge, Rake でない場合は使用されない想定。
    vector<V> dp_v; // stt の各頂点に対応するクラスタの答え。頂点が Vertex, AddVertex, Compress でない場合は使用されない想定。

    StaticTopTreeDp(vector<vector<pair<int, int>>> G,
                    function<V(int)> vertex,
                    function<E(V, int)> add_edge,
                    function<E(E, E)> rake,
                    function<V(E, int)> add_vertex,
                    function<V(V, V, int)> compress,
                    int root = 0)
        : vertex(vertex), add_edge(add_edge), rake(rake), add_vertex(add_vertex), compress(compress) {

        child.resize(G.size() - 1, -1);
        preprocess_graph(G, root, -1);

        stt = StaticTopTree(G, root);

        dp_e.resize(stt.size());
        dp_v.resize(stt.size());
    }

    V fill_dp_all() {
        // DP を全て埋める。最初に一度だけ呼ばれる想定。
        dfs(stt.stt_root);
        return dp_v[stt.stt_root];
    }

    V update_vertex(int u) {
        // 頂点 u の値が変わった後に、その影響を木 DP に反映する。O(log n)
        while (u != -1) {
            update(u);
            u = stt.P[u];
        }
        return dp_v[stt.stt_root];
    }

    V update_edge(int e) {
        // 辺 e の値が変わった後に、その影響を木 DP に反映する。O(log n)
        return update_vertex(child[e]);
    }

  private:
    void preprocess_graph(vector<vector<pair<int, int>>> &G, int now, int par) {
        int par_idx = -1;
        for (int i = 0; i < (int)G[now].size(); i++) {
            if (G[now][i].first == par) {
                par_idx = i;
            } else {
                child[G[now][i].second] = G[now][i].first;
                preprocess_graph(G, G[now][i].first, now);
            }
        }
        if (par_idx != -1) {
            swap(G[now][par_idx], G[now].back());
            G[now].pop_back();
        }
    }

    void update(int u) {
        if (stt.T[u] == Type::Vertex) {
            dp_v[u] = vertex(u);
        } else if (stt.T[u] == Type::Compress) {
            dp_v[u] = compress(dp_v[stt.L[u]], dp_v[stt.R[u]], stt.merged_edge[u]);
        } else if (stt.T[u] == Type::Rake) {
            dp_e[u] = rake(dp_e[stt.L[u]], dp_e[stt.R[u]]);
        } else if (stt.T[u] == Type::AddEdge) {
            dp_e[u] = add_edge(dp_v[stt.L[u]], stt.merged_edge[u]);
        } else {
            dp_v[u] = add_vertex(dp_e[stt.L[u]], u);
        }
    }

    void dfs(int now) {
        if (stt.L[now] != -1) dfs(stt.L[now]);
        if (stt.R[now] != -1) dfs(stt.R[now]);
        update(now);
    }
};