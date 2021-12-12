//*
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//*/

#include <bits/stdc++.h>

// #include <atcoder/all>
// #include <atcoder/maxflow>

using namespace std;
// using namespace atcoder;

#define DEBUG(x) cerr << #x << ": " << x << endl;
#define DEBUG_VEC(v)                                        \
    cerr << #v << ":";                                      \
    for (int iiiiiiii = 0; iiiiiiii < v.size(); iiiiiiii++) \
        cerr << " " << v[iiiiiiii];                         \
    cerr << endl;
#define DEBUG_MAT(v)                                \
    cerr << #v << endl;                             \
    for (int iv = 0; iv < v.size(); iv++) {         \
        for (int jv = 0; jv < v[iv].size(); jv++) { \
            cerr << v[iv][jv] << " ";               \
        }                                           \
        cerr << endl;                               \
    }
typedef long long ll;
// #define int ll

#define vi vector<int>
#define vl vector<ll>
#define vii vector<vector<int>>
#define vll vector<vector<ll>>
#define vs vector<string>
#define pii pair<int, int>
#define pis pair<int, string>
#define psi pair<string, int>
#define pll pair<ll, ll>
template <class S, class T>
pair<S, T> operator+(const pair<S, T> &s, const pair<S, T> &t) {
    return pair<S, T>(s.first + t.first, s.second + t.second);
}
template <class S, class T>
pair<S, T> operator-(const pair<S, T> &s, const pair<S, T> &t) { return pair<S, T>(s.first - t.first, s.second - t.second); }
template <class S, class T>
ostream &operator<<(ostream &os, pair<S, T> p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
#define X first
#define Y second
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n)-1; i >= 0; i--)
#define rrep1(i, n) for (int i = (int)(n); i > 0; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define in(x, a, b) (a <= x && x < b)
#define all(c) c.begin(), c.end()
void YES(bool t = true) {
    cout << (t ? "YES" : "NO") << endl;
}
void Yes(bool t = true) { cout << (t ? "Yes" : "No") << endl; }
void yes(bool t = true) { cout << (t ? "yes" : "no") << endl; }
void NO(bool t = true) { cout << (t ? "NO" : "YES") << endl; }
void No(bool t = true) { cout << (t ? "No" : "Yes") << endl; }
void no(bool t = true) { cout << (t ? "no" : "yes") << endl; }
template <class T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}
#define UNIQUE(v) v.erase(std::unique(v.begin(), v.end()), v.end());
const ll inf = 1000000001;
const ll INF = (ll)1e18 + 1;
const long double pi = 3.1415926535897932384626433832795028841971L;
int popcount(ll t) { return __builtin_popcountll(t); }
// int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
// int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };
vi dx = {0, 1, 0, -1}, dy = {-1, 0, 1, 0};
// vi dx2 = { 1,1,0,-1,-1,-1,0,1 }, dy2 = { 0,1,1,1,0,-1,-1,-1 };
struct Setup_io {
    Setup_io() {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
        cout << fixed << setprecision(25);
    }
} setup_io;
// const ll MOD = 1000000007;
const ll MOD = 998244353;
// #define mp make_pair
//#define endl '\n'

uint32_t xor_shift() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

uint32_t rnd(int l, int r) {
    auto res = xor_shift();

    res %= (r - l);
    return l + res;
}

uint32_t rnd(int r) {
    return rnd(0, r);
}

class UnionFind {
  private:
    vi par_;      //�e
    vi ran_;      //�؂̐[��
    vi num_;      //�v�f��
    vi edge_num_; //�v�f��
  public:
    int n;
    int g; // group��

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

    //�؂̍������߂�
    int find(int x) {
        if (par_[x] == x) {
            return x;
        } else {
            return par_[x] = find(par_[x]);
        }
    }

    //x��y�̑�����W���𕹍�
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

    //x��y�������W���ɑ����邩�ۂ�
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

constexpr int n = 400, m = 1995;
vector<pii> xy(n);
vector<pii> edges(m);
vii e_table(n, vi(n, -1));
void input() {
    rep(i, n) {
        cin >> xy[i].first >> xy[i].second;
    }
    rep(i, m) {
        cin >> edges[i].first >> edges[i].second;
        auto [u, v] = edges[i];
        e_table[u][v] = e_table[v][u] = i;
    }
}

int dist(pii xy1, pii xy2) {
    pii xy = xy1 - xy2;
    return round(sqrt(xy.first * xy.first + xy.second * xy.second));
}

using P = pair<pii, pii>;
int kruskal(vector<P> es, const vector<int> &kakutei, vector<int> &res, vii &G) {
    fill(all(res), 0);
    fill(all(G), vi());

    sort(all(es));
    UnionFind uf(n);

    int score = 0;
    rep(i, es.size()) {
        int idx = es[i].first.second;

        if (kakutei[idx] == 1) {
            auto [u, v] = es[i].second;
            uf.unite(u, v);
            G[u].push_back(v);
            G[v].push_back(u);
            res[idx] = true;
            score += es[i].first.first;
        }
    }

    rep(i, es.size()) {
        auto [u, v] = es[i].second;
        if (uf.same(u, v)) continue;
        int idx = es[i].first.second;
        if (kakutei[idx] == -1) continue;
        assert(kakutei[idx] == 0);

        uf.unite(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
        res[idx] = true;
        score += es[i].first.first;
    }
    if (uf.g > 1) return inf;
    return score;
}

signed main() {
    input();
    int score = 0;
    UnionFind uf(n);

    vector<P> es(m);
    vector<int> kakutei(m);
    rep(i, m) {
        auto [u, v] = edges[i];
        es[i].first = pii(dist(xy[u], xy[v]) * 2, i);
        es[i].second = edges[i];
    }
    vector<int> use(m), nuse(m);
    vii G(n), nG(n);
    kruskal(es, kakutei, use, G);

    rep(i, m) {
        int d;
        cin >> d;
        auto [u, v] = edges[i];
        if (uf.same(u, v)) {
            cout << 0 << endl;
            kakutei[i] = -1;
            continue;
        }

        es[i].first.first = d;
        kruskal(es, kakutei, use, G);

        if (use[i]) {
            UnionFind uf2(n);
            rep(j, m) {
                auto [u, v] = edges[j];
                if (use[j] && j != i) uf2.unite(u, v);
            }
            assert(uf2.g == 2);

            vi ds;
            rep(j, m) {
                if (j == i) continue;
                if (kakutei[j] != 0) continue;
                auto [u, v] = edges[j];
                if (!uf2.same(u, v)) {
                    ds.push_back(es[j].first.first / 2);
                }
            }

            // p1: d が最小となる確率
            double p1 = 1.0001;
            for (int d2 : ds) {
                p1 *= min(max((double)(3 * d2 - d) / (2 * d2), 0.0), 1.0);
            }

            if (p1 >= 1.0 / (ds.size() + 1)) {
                uf.unite(u, v);
                score += d;
                cout << 1 << endl;
                kakutei[i] = 1;
            } else {
                cout << 0 << endl;
                kakutei[i] = -1;
            }
        } else {
            vi path = find_path(G, u, v);
            vi und;
            // DEBUG(pii(u, v));
            // DEBUG_VEC(path);
            rep(ii, path.size() - 1) {
                int u = path[ii];
                int v = path[ii + 1];
                int idx = e_table[u][v];
                assert(idx != i);
                if (kakutei[idx] != 0) continue;
                und.push_back(idx);
            }
            assert(und.size() > 0);

            // p1: i が最大の確率
            double p1 = 1.0;
            int mi_d = inf;
            for (int idx : und) {
                int ori = es[idx].first.first / 2;
                p1 *= min(max((double)(d - ori) / (2 * ori), 0.0), 1.0);
            }

            // p2: i より mi_ori が上回る確率
            // double p2 = (d - mi_d) / (2 * mi_d)

            if (p1 < 1.0 / (und.size() + 1)) {
                uf.unite(u, v);
                score += d;
                cout << 1 << endl;
                kakutei[i] = 1;
            } else {
                cout << 0 << endl;
                kakutei[i] = -1;
            }
        }

        // if (i == 30) break;
    }
    DEBUG(score);
}
