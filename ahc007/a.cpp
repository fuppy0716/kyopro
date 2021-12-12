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
#define int ll

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
    vi par_; //�e
    vi ran_; //�؂̐[��
  public:
    int n;
    int g; // group��

    UnionFind(int _n) {
        n = _n;
        par_.resize(n);
        ran_.resize(n);
        reset(_n);
    }

    void reset(int _n) {
        n = _n;
        g = n;
        for (int i = 0; i < n; i++) {
            par_[i] = i;
            ran_[i] = 0;
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
        if (x == y) {
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
        g--;
    }

    //x��y�������W���ɑ����邩�ۂ�
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

constexpr int n = 400, m = 1995;
vector<pii> xy(n);
vector<pii> edges(m);
void input() {
    rep(i, n) {
        cin >> xy[i].first >> xy[i].second;
    }
    rep(i, m) {
        cin >> edges[i].first >> edges[i].second;
    }
}

int dist(pii xy1, pii xy2) {
    pii xy = xy1 - xy2;
    return round(sqrt(xy.first * xy.first + xy.second * xy.second));
}

using P = pair<pii, pii>;
int kruskal(vector<P> es, const vector<P> kakutei, vector<int> &res, int tar) {
    auto [tu, tv] = es[m - 1 - tar].second;

    res[tar] = 0;
    sort(all(es));
    static UnionFind uf(n);
    uf.reset(n);

    int score = 0;
    rep(i, kakutei.size()) {
        int idx = kakutei[i].first.second;

        auto [u, v] = kakutei[i].second;
        assert(!uf.same(u, v));
        uf.unite(u, v);
        res[idx] = true;
        score += kakutei[i].first.first;
    }

    rep(i, es.size()) {
        auto [u, v] = es[i].second;
        if (uf.same(u, v)) continue;
        int idx = es[i].first.second;

        uf.unite(u, v);
        res[idx] = true;
        score += es[i].first.first;

        if (tar != -1 && tar == idx) return 0;
        if (uf.same(tu, tv)) return 0;
    }
    if (uf.g > 1) return inf;
    return score;
}

signed main() {
    input();
    int score = 0;
    UnionFind uf(n);

    vector<P> es(m);
    vi dists(m);
    rep(i, m) {
        auto [u, v] = edges[i];
        es[i].first = pii(dist(xy[u], xy[v]) * 2, i);
        es[i].second = edges[i];
        dists[i] = es[i].first.first / 2;
    }
    vector<int> use(m);

    reverse(all(es));
    vector<P> kaku;

    rep(i, m) {
        int d;
        cin >> d;
        es.back().first.first = d;

        auto [u, v] = edges[i];
        if (uf.same(u, v)) {
            cout << 0 << endl;
            es.pop_back();
            continue;
        }

        int use_cnt = 0, not_cnt = 0;
        int max_try_num = 99;
        int diff = 11;
        int straight = 6;
        rep(try_num, max_try_num) {
            for (int j = 0; j < es.size() - 1; j++) {
                int d = dists[m - 1 - j];
                es[j].first.first = rnd(d, 3 * d + 1);
            }
            int new_score = kruskal(es, kaku, use, i);

            if (use[i]) {
                use_cnt++;
            } else {
                not_cnt++;
            }

            if ((use_cnt == 0 || not_cnt == 0) && (use_cnt + not_cnt == straight)) break;
            if (abs(use_cnt - not_cnt) == diff) break;
        }

        if (use_cnt >= not_cnt) {
            uf.unite(u, v);
            score += d;
            cout << 1 << endl;
            kaku.push_back(es.back());
            es.pop_back();
        } else {
            cout << 0 << endl;
            es.pop_back();
        }

        // if (i == 30) break;
    }
    assert(es.size() == 0);
    assert(kaku.size() == n - 1);
    DEBUG(score);
}
