
class UnionFind {
  private:
    vi par_;
    vi ran_;
    vi num_;
    vi edge_num_;

  public:
    int n;
    int g;

    UnionFind(int _n) {
        n = _n;
        g = n;
        par_.resize(n);
        ran_.resize(n);
        num_.resize(n);
        edge_num_.resize(n);
        for (int i = 0; i < n; i++) {
            par_[i] = i;
            ran_[i] = 0;
            num_[i] = 1;
            edge_num_[i] = 0;
        }
    }

    int find(int x) {
        if (par_[x] == x) {
            return x;
        } else {
            return par_[x] = find(par_[x]);
        }
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        int numsum = num_[x] + num_[y];
        int edge_numsum = edge_num_[x] + edge_num_[y];
        if (x == y) {
            edge_num_[x]++;
            return;
        }
        if (ran_[x] < ran_[y]) {
            par_[x] = y;
        } else {
            par_[y] = x;
            if (ran_[x] == ran_[y]) {
                ran_[x]++;
            }
        }
        num_[x] = num_[y] = numsum;
        edge_num_[x] = edge_num_[y] = edge_numsum + 1;
        g--;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int num(int x) {
        return num_[find(x)];
    }

    int edge_num(int x) {
        return edge_num_[find(x)];
    }
};

// ���_�ɒl���ڂ��Ă��鎞
// https://yukicoder.me/submissions/410940
// �ӂɒl���ڂ��Ă��鎞
// https://yukicoder.me/submissions/410947
// https://atcoder.jp/contests/abc133/submissions/9120584
// ���_�ɒl���ڂ��Ă��鎞�C�����؃N�G��
// https://atcoder.jp/contests/iroha2019-day2/submissions/9039015
// http://beet-aizu.hatenablog.com/entry/2017/12/12/235950
//  move
//  https://judge.yosupo.jp/submission/97270
class HLD {
  private:
    void dfs_sz(int v) {
        for (int &u : G[v])
            if (u == par[v]) swap(u, G[v].back());
        if (~par[v]) G[v].pop_back();

        for (int &u : G[v]) {
            par[u] = v;
            dep[u] = dep[v] + 1;
            dfs_sz(u);
            sub[v] += sub[u];
            if (sub[u] > sub[G[v][0]]) swap(u, G[v][0]);
        }
    }

    void dfs_hld(int v, int c, int &pos) {
        vid[v] = pos++;
        inv[vid[v]] = v;
        type[v] = c;
        for (int u : G[v]) {
            if (u == par[v]) continue;
            head[u] = (u == G[v][0] ? head[v] : u);
            dfs_hld(u, c, pos);
        }
    }

  public:
    vector<vector<int>> G;
    vector<int> vid, head, sub, par, dep, inv, type;

    HLD(int n) : G(n), vid(n, -1), head(n), sub(n, 1),
                 par(n, -1), dep(n, 0), inv(n), type(n) {}

    void add_edge(int u, int v) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void build(vector<int> rs = {0}) {
        int c = 0, pos = 0;
        for (int r : rs) {
            dfs_sz(r);
            head[r] = r;
            dfs_hld(r, c++, pos);
        }
    }

    bool is_subtree(int c, int p) {
        // c が p の部分木に含まれるか
        return vid[c] >= vid[p] && vid[c] < vid[p] + sub[p];
    }

    int lca(int u, int v) {
        while (1) {
            if (vid[u] > vid[v]) swap(u, v);
            if (head[u] == head[v]) return u;
            v = par[head[v]];
        }
    }

    // move d from u to v
    // if d == 0: return u
    // if d == dist(u, v): return v
    int move(int u, int v, int d) {
        int full_d = distance(u, v);

        assert(d <= full_d);

        // following to lca, move from v
        d = full_d - d;
        while (1) {
            if (vid[u] > vid[v]) {
                swap(u, v);
                d = full_d - d;
            }

            int to_head_d = vid[v] - vid[head[v]];

            if (to_head_d >= d) {
                return inv[vid[v] - d];
            }
            v = par[head[v]];
            d -= to_head_d + 1;
            full_d -= to_head_d + 1;
        }
    }

    int distance(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    // for_each(vertex)
    // [l, r) <- attention!!
    template <typename F>
    void for_each(int u, int v, const F &f) {
        while (1) {
            if (vid[u] > vid[v]) swap(u, v);
            f(max(vid[head[v]], vid[u]), vid[v] + 1);
            if (head[u] != head[v])
                v = par[head[v]];
            else
                break;
        }
    }

    template <typename T, typename Q, typename F>
    T for_each(int u, int v, T ti, const Q &q, const F &f) {
        T l = ti, r = ti;
        while (1) {
            if (vid[u] > vid[v]) {
                swap(u, v);
                swap(l, r);
            }
            l = f(l, q(max(vid[head[v]], vid[u]), vid[v] + 1));
            if (head[u] != head[v])
                v = par[head[v]];
            else
                break;
        }
        return f(l, r);
    }

    // for_each(edge)
    // [l, r) <- attention!!
    template <typename F>
    void for_each_edge(int u, int v, const F &f) {
        while (1) {
            if (vid[u] > vid[v]) swap(u, v);
            if (head[u] != head[v]) {
                f(vid[head[v]], vid[v] + 1);
                v = par[head[v]];
            } else {
                if (u != v) {
                    f(vid[u] + 1, vid[v] + 1);
                }
                break;
            }
        }
    }
};

// https://codeforces.com/contest/1967/submission/258981590
struct DirectedNamori {
    // 頂点 u から頂点 parent[u] に親辺が張られているような Namori グラフを扱う
    // 各連結成分は一つのサイクルと、サイクル上の頂点を根とする木からなる

    int n;
    vector<int> parent;

    UnionFind uf;
    vector<int> is_in_cycle; // 各頂点がサイクル上にあるか
    vector<int> cycle_ord;   // 各頂点がサイクル上で何番目の頂点か。サイクル内の相対的な距離関係のために使用
    vector<int> cycle_size;  // 各サイクルの大きさ

    vector<vector<int>> forest; // サイクル上の各頂点を根とする木。子への辺のみを持つ
    vector<int> root;           // 各頂点の根
    vector<int> depth;          // 各頂点の深さ。サイクル上の頂点は 0、それ以外は親の深さ + 1
    HLD hld;

    DirectedNamori(vi p) : n(p.size()), parent(p), uf(n), is_in_cycle(n), cycle_ord(n, -1), cycle_size(n), forest(n), root(n), depth(n), hld(n) {
        rep(u, n) {
            uf.unite(u, p[u]);
        }

        vector<int> seen(n);
        rep(u, n) {
            if (uf.find(u) != u) {
                continue;
            }
            // u が属する連結成分について、サイクル上の頂点を is_in_cycle に記録
            vi path;
            dfs_fill_cycle(u, seen, path);
        }

        rep(u, n) {
            int v = p[u];
            if (not(is_in_cycle[u] and is_in_cycle[v])) {
                forest[v].push_back(u);
                hld.add_edge(u, v);
            }
        }

        vector<int> rs;
        rep(u, n) {
            if (is_in_cycle[u]) {
                rs.push_back(u);
                dfs_fill_root(u, u, 0);
            }
        }

        hld.build(rs);
    }

    int distance(int u, int v) {
        // u から v に親辺のみを使って移動する距離
        // 移動できない場合は -1
        if (!uf.same(u, v)) {
            return -1;
        }
        if (is_in_cycle[u]) {
            if (is_in_cycle[v]) {
                return distance_cycle(u, v);
            } else {
                return -1;
            }
        }

        if (is_in_cycle[v]) {
            return depth[u] + distance_cycle(root[u], v);
        } else {
            if (root[u] == root[v]) {
                return distance_tree(u, v);
            } else {
                return -1;
            }
        }
    }

    int distance_cycle(int u, int v) {
        // u と v が同じサイクル内にある前提で、u から v に移動する距離
        assert(uf.same(u, v));
        assert(is_in_cycle[u] and is_in_cycle[v]);
        return (cycle_ord[v] - cycle_ord[u] + cycle_size[v]) % cycle_size[v];
    }

    int distance_tree(int u, int v) {
        // u と v が同じ木内にある前提で、u から v に移動する距離
        assert(uf.same(u, v));
        assert(root[u] == root[v]);

        if (hld.is_subtree(u, v)) {
            return depth[u] - depth[v];
        } else {
            return -1;
        }
    }

  private:
    void dfs_fill_cycle(int u, vector<int> &seen, vector<int> &path) {
        if (seen[u]) {
            int start_idx = -1;
            for (int i = 0; i < path.size(); i++) {
                if (path[i] == u) {
                    start_idx = i;
                    break;
                }
            }
            for (int i = start_idx; i < path.size(); i++) {
                is_in_cycle[path[i]] = true;
                cycle_ord[path[i]] = i;
                cycle_size[path[i]] = path.size() - start_idx;
            }
            return;
        }
        seen[u] = true;
        path.push_back(u);
        dfs_fill_cycle(parent[u], seen, path);
    }

    void dfs_fill_root(int u, int r, int d) {
        root[u] = r;
        depth[u] = d;
        for (int v : forest[u]) {
            dfs_fill_root(v, r, d + 1);
        }
    }
};
