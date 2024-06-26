
class CentroidDecomposition {
  public:
    int n;               // ���_��
    vii G;               // �O���t�̗אڃ��X�g�\��
    vector<bool> isused; // ���̒��_�����łɕ����Ɏg���Ă��邩
    vi subtreesize;      // �����؂̃T�C�Y,�X�V�����
    vi parent;
    vi centroid; // �d�S�����ɒǉ�����Ă���
    vector<char> ans;

    CentroidDecomposition(int n) : n(n) {
        G.resize(n);
        isused.resize(n);
        subtreesize.resize(n);
        parent.resize(n);
        ans.resize(n);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int search_centroid(int now, int par, int size) {
        subtreesize[now] = 1;
        parent[now] = par;
        bool iscentroid = true;
        for (int i = 0; i < G[now].size(); i++) {
            int child = G[now][i];
            if (child == par) continue;
            if (isused[child]) continue;
            int child_size = search_centroid(child, now, size);
            if (child_size > size / 2) iscentroid = false;
            subtreesize[now] += child_size;
        }
        if (size - subtreesize[now] > size / 2) {
            iscentroid = false;
        }
        if (iscentroid) {
            centroid.push_back(now);
        }
        return subtreesize[now];
    }

    // ���ɂ���ĕς��
    void solve(int root, char c, int size) {
        search_centroid(root, -1, size);
        int cent = centroid.back();
        isused[cent] = true;
        ans[cent] = c;
        rep(i, G[cent].size()) {
            int ch = G[cent][i];
            if (isused[ch]) {
                continue;
            }
            if (parent[ch] == cent) {
                solve(ch, c + 1, subtreesize[ch]);
            } else {
                solve(ch, c + 1, size - subtreesize[cent]);
            }
        }
        return;
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

struct AuxiliaryTree {
    // see: https://smijake3.hatenablog.com/entry/2019/09/15/200200
    // verify: https://atcoder.jp/contests/abc359/submissions/54857535
    // verify: https://atcoder.jp/contests/abc340/submissions/54857662

    int n;

    // 行先の頂点、距離
    vector<vector<pair<int, long long>>> G_ori;
    vector<vector<pair<int, long long>>> G;
    int root;
    HLD hld;

    // order[u]: u が何番目に処理されるか
    vector<int> order;
    vector<long long> depth;

    // 後片付け用
    vector<int> prev_uses;

    AuxiliaryTree(vii G_) : n(G_.size()), hld(n) {
        G_ori.resize(n);

        for (int i = 0; i < n; i++) {
            for (auto p : G_[i]) {
                G_ori[i].push_back({p, 1});
            }
        }
        init();
    }

    void init() {
        // G_ori のみ初期化済み
        for (int u = 0; u < n; u++) {
            for (auto [v, _] : G_ori[u]) {
                if (u < v) {
                    hld.add_edge(u, v);
                }
            }
        }
        hld.build();

        G.resize(n);
        order.resize(n);
        depth.resize(n);

        int ord = 0;
        pre_dfs(0, -1, ord, 0);
    }

    int build(vector<int> vs) {
        // 前回のクエリの後片付け
        for (int u : prev_uses) {
            G[u].clear();
        }
        prev_uses.clear();

        if (vs.size() == 0) {
            assert(false);
        }

        // 頂点 vs とその LCA からなる補助木を構築
        sort(all(vs), [&](int u, int v) { return order[u] < order[v]; });

        stack<int> st;
        st.push(vs[0]);
        for (int i = 1; i < vs.size(); i++) {
            int v = vs[i];
            int w = hld.lca(st.top(), v);

            while (!st.empty()) {
                int u = st.top();
                if (depth[u] <= depth[w]) {
                    break;
                }
                st.pop();

                int par;
                if (st.size() == 0) {
                    par = w;
                } else {
                    int to = st.top();
                    if (depth[to] > depth[w]) {
                        par = to;
                    } else {
                        // 次に w が push される
                        par = w;
                    }
                }

                prev_uses.push_back(u);
                G[par].push_back({u, depth[u] - depth[par]});
                G[u].push_back({par, depth[u] - depth[par]});
            }
            if (st.empty() || st.top() != w) {
                st.push(w);
            }
            st.push(v);
        }

        while (st.size() >= 1) {
            int u = st.top();
            st.pop();
            prev_uses.push_back(u);
            if (st.size() >= 1) {
                int v = st.top();
                G[v].push_back({u, depth[u] - depth[v]});
                G[u].push_back({v, depth[u] - depth[v]});
            } else {
                root = u;
            }
        }
        return root;
    }

  private:
    void pre_dfs(int v, int p, int &ord, int dep) {
        order[v] = ord++;
        depth[v] = dep;
        for (auto [ch, d] : G_ori[v]) {
            if (ch == p) continue;
            pre_dfs(ch, v, ord, d + dep);
        }
    }
};

// ���t���؂̃n�b�V��
// �؂̓��^����Ɏg��
#include <random>
vl rand1(100010);
vl rand2(100010);

void make_rand() {
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randinf(0, inf);
    rep(i, 100010) {
        rand1[i] = randinf(mt);
        rand2[i] = randinf(mt);
    }
}

pll hs(vii &G, int now, int parent, int depth) {
    pll res = pll(1, 1);
    rep(i, G[now].size()) {
        if (G[now][i] == parent) {
            continue;
        }
        pll temp = hs(G, G[now][i], now, depth + 1);
        (res.first *= (temp.first + rand1[depth])) %= mod;
        (res.second *= (temp.second + rand2[depth])) %= mod;
    }
    return res;
}

// 直径、（端点1, 端点2）
pair<int, pii> diameter(vii G) {
    int n = G.size();
    vi dist(n);
    function<void(int, int, int, vii &, vi &)> dfs = [&dfs](int now, int par, int d, vii &G, vi &dist) {
        dist[now] = d;
        for (int ch : G[now]) {
            if (ch == par) continue;
            dfs(ch, now, d + 1, G, dist);
        }
    };
    dfs(0, -1, 0, G, dist);
    pii ma(-1, -1);
    rep(i, n) chmax(ma, pii(dist[i], i));
    int u = ma.second;

    dfs(u, -1, 0, G, dist);

    ma = pii(-1, -1);
    rep(i, n) chmax(ma, pii(dist[i], i));
    int v = ma.second;
    return make_pair(ma.first, pii(u, v));
}

// 直径、（端点1, 端点2）
pair<ll, pii> diameter(vector<vector<pll>> G) {
    // vector<vector<pair<Cost, To>>> G
    int n = G.size();
    vl dist(n);
    function<void(int, int, ll, vector<vector<pll>> &, vl &)> dfs = [&dfs](int now, int par, ll d, vector<vector<pll>> &G, vl &dist) {
        dist[now] = d;
        for (auto [cost, ch] : G[now]) {
            if (ch == par) continue;
            dfs(ch, now, d + cost, G, dist);
        }
    };
    dfs(0, -1, 0, G, dist);
    pll ma(-1, -1);
    rep(i, n) chmax(ma, pll(dist[i], i));
    int u = ma.second;

    dfs(u, -1, 0, G, dist);

    ma = pll(-1, -1);
    rep(i, n) chmax(ma, pll(dist[i], i));
    int v = ma.second;
    return make_pair(ma.first, pii(u, v));
}

// u -> v のパスを返す
vector<int> find_path(vii &G, int u, int v) {
    int n = G.size();

    vi path;
    function<bool(int, int, int, vii &, vi &)> dfs = [&dfs](int now, int par, int tar, vii &G, vi &path) {
        if (now == tar) {
            path.push_back(now);
            return true;
        }
        for (int ch : G[now]) {
            if (ch == par) continue;
            if (dfs(ch, now, tar, G, path)) {
                path.push_back(now);
                return true;
            }
        }
        return false;
    };

    dfs(u, -1, v, G, path);
    reverse(all(path));
    return path;
}
