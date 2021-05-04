/*
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//*/

#include <bits/stdc++.h>

// #include <atcoder/all>

using namespace std;
// using namespace atcoder;

#define DEBUG(x) cerr << #x << ": " << x << endl;
#define DEBUG_VEC(v)                   \
    cerr << #v << ":";                 \
    for (int i = 0; i < v.size(); i++) \
        cerr << " " << v[i];           \
    cerr << endl;
#define DEBUG_MAT(v)                            \
    cerr << #v << endl;                         \
    for (int i = 0; i < v.size(); i++) {        \
        for (int j = 0; j < v[i].size(); j++) { \
            cerr << v[i][j] << " ";             \
        }                                       \
        cerr << endl;                           \
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
pair<S, T> operator+(const pair<S, T> &s, const pair<S, T> &t) { return pair<S, T>(s.first + t.first, s.second + t.second); }
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
void YES(bool t = true) { cout << (t ? "YES" : "NO") << endl; }
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
// const ll MOD = 998244353;
// #define mp make_pair
//#define endl '\n'

// 辺の削除が O(1) でできる無向グラフ
// G[u] 上での並びが重要な時には適用不能
// 自己ループがある際には適用不能
class ErasableGraph {
    void _erase(int u, int i) {
        int i2 = (int)G[u].size() - 1;
        swap(G[u][i], G[u][i2]);
        swap(partner_position[u][i], partner_position[u][i2]);
        G[u].pop_back();
        partner_position[u].pop_back();
        if (i == i2) return;

        int v = G[u][i];
        int j = partner_position[u][i];
        assert(G[v][j] == u);
        partner_position[v][j] = i;
    }

  public:
    int n;
    vii G;
    vii partner_position;

    ErasableGraph(int n = 0) : n(n), G(n), partner_position(n) {}

    void add_edge(int u, int v) {
        assert(u != v);
        G[u].push_back(v);
        partner_position[u].push_back(G[v].size());
        G[v].push_back(u);
        partner_position[v].push_back((int)G[u].size() - 1);
    }

    // u の i 番目の辺を削除する
    void erase(int u, int i) {
        int v = G[u][i];
        int j = partner_position[u][i];

        _erase(u, i);
        _erase(v, j);
    }
};

template <typename T>
class ErasableWeightedGraph {
    void _erase(int u, int i) {
        int i2 = (int)G[u].size() - 1;
        swap(G[u][i], G[u][i2]);
        swap(partner_position[u][i], partner_position[u][i2]);
        G[u].pop_back();
        partner_position[u].pop_back();
        if (i == i2) return;

        int v = G[u][i].first;
        int j = partner_position[u][i];
        assert(G[v][j].first == u);
        partner_position[v][j] = i;
    }

  public:
    int n;
    vector<vector<pair<int, T>>> G;
    vii partner_position;

    ErasableWeightedGraph(int n = 0) : n(n), G(n), partner_position(n) {}

    void add_edge(int u, int v, T w) {
        assert(u != v);
        G[u].push_back({v, w});
        partner_position[u].push_back(G[v].size());
        G[v].push_back({u, w});
        partner_position[v].push_back((int)G[u].size() - 1);
    }

    // u の i 番目の辺を削除する
    void erase(int u, int i) {
        int v = G[u][i].first;
        int j = partner_position[u][i];

        _erase(u, i);
        _erase(v, j);
    }
};

struct dice {
    mt19937 mt;
    dice() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    // [0, x)の一様乱数
    ll operator()(ll x) { return this->operator()(0, x); }
    // [x, y)の一様乱数
    ll operator()(ll x, ll y) {
        uniform_int_distribution<ll> dist(x, y - 1);
        return dist(mt);
    }
    vl operator()(int n, ll x, ll y) {
        vl res(n);
        for (int i = 0; i < n; i++)
            res[i] = this->operator()(x, y);
        return res;
    }
} rnd;

signed main() {
    int n, m;
    cin >> n >> m;
    // vii G(n);
    ErasableGraph GG(n);
    vector<pii> es;
    map<pii, int> mp;
    rep(i, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        GG.add_edge(u, v);
        es.emplace_back(u, v);
        mp[pii(u, v)] = mp[pii(v, u)] = i;
        // G[u].push_back(v);
        // G[v].push_back(u);
    }

    vector<bool> used(m, true);
    rep(_, 10000) {
        int idx = rnd(m);
        if (used[idx]) {
            int u = es[idx].first;
            int j = rnd(GG.G[u].size());
            int v = GG.G[u][j];
            GG.erase(u, j);
            used[mp[pii(u, v)]] = false;
        } else {
            GG.add_edge(es[idx].first, es[idx].second);
            used[idx] = true;
        }
    }
    rep(idx, m) {
        if (not used[idx]) {
            GG.add_edge(es[idx].first, es[idx].second);
        }
    }

    auto G = GG.G;

    vi ans(n, -1);

    queue<int> qu;
    qu.push(0);
    while (qu.size()) {
        int u = qu.front();
        qu.pop();
        for (int v : G[u]) {
            if (ans[v] != -1) continue;
            ans[v] = u;
            qu.push(v);
        }
    }

    cout << "Yes" << endl;
    rep1(i, n - 1) {
        cout << ans[i] + 1 << endl;
    }
}
