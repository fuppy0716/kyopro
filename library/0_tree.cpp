
class CentroidDecomposition {
  public:
    int n;               //���_��
    vii G;               //�O���t�̗אڃ��X�g�\��
    vector<bool> isused; //���̒��_�����łɕ����Ɏg���Ă��邩
    vi subtreesize;      //�����؂̃T�C�Y,�X�V�����
    vi parent;
    vi centroid; //�d�S�����ɒǉ�����Ă���
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

    //���ɂ���ĕς��
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

//���_�ɒl���ڂ��Ă��鎞
//https://yukicoder.me/submissions/410940
//�ӂɒl���ڂ��Ă��鎞
//https://yukicoder.me/submissions/410947
//https://atcoder.jp/contests/abc133/submissions/9120584
//���_�ɒl���ڂ��Ă��鎞�C�����؃N�G��
//https://atcoder.jp/contests/iroha2019-day2/submissions/9039015
//http://beet-aizu.hatenablog.com/entry/2017/12/12/235950
// move
// https://judge.yosupo.jp/submission/97270
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

//���t���؂̃n�b�V��
//�؂̓��^����Ɏg��
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
