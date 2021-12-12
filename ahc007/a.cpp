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
int kruskal(vector<P> es, const vector<int> &kakutei, vector<int> &res) {
    fill(all(res), 0);
    sort(all(es));
    UnionFind uf(n);

    int score = 0;
    rep(i, es.size()) {
        int idx = es[i].first.second;

        if (kakutei[idx] == 1) {
            auto [u, v] = es[i].second;
            uf.unite(u, v);
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
    vector<int> use(m);
    int ori_score = kruskal(es, kakutei, use);
    DEBUG(ori_score);
    assert(es[0].first.first = 68);
    es[0].first.first++;
    int new_score = kruskal(es, kakutei, use);
    DEBUG(new_score);

    vector<int> new_use(m), no_use(m);
    rep(i, m) {
        int d;
        cin >> d;
        auto [u, v] = edges[i];
        if (uf.same(u, v)) {
            cout << 0 << endl;
            kakutei[i] = -1;
            continue;
        }

        kakutei[i] = -1;
        int diff = d - es[i].first.first;
        DEBUG(pii(es[i].first.first, d));
        es[i].first.first = d;
        int no_score = kruskal(es, kakutei, no_use);
        DEBUG(no_score);

        kakutei[i] = 1;
        new_score = kruskal(es, kakutei, new_use);

        if (no_score == inf) {
            uf.unite(u, v);
            score += d;
            cout << 1 << endl;
            kakutei[i] = 1;
            ori_score = new_score;
            continue;
        }

        DEBUG(pii(ori_score, new_score));
        DEBUG(diff);

        bool is_use = false;
        if (use[i]) {
            is_use = (new_score <= ori_score + diff);
        } else {
            is_use = new_score <= ori_score;
        }

        if (is_use) {
            uf.unite(u, v);
            score += d;
            cout << 1 << endl;
            kakutei[i] = 1;
            ori_score = new_score;
        } else {
            cout << 0 << endl;
            kakutei[i] = -1;
            ori_score = no_score;
        }

        // if (i == 30) break;
    }
    DEBUG(score);
}
