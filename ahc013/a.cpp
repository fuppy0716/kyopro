//*
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//*/

#include <bits/stdc++.h>

// #include <atcoder/all>

using namespace std;
// using namespace atcoder;

// #define _GLIBCXX_DEBUG

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
vi dx = {0, 0, -1, 1}, dy = {-1, 1, 0, 0};
vi dx2 = {1, 1, 0, -1, -1, -1, 0, 1}, dy2 = {0, 1, 1, 1, 0, -1, -1, -1};
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

clock_t start_c;

int n, k;
vii c;

void input() {
    cin >> n >> k;
    c.resize(n);
    rep(i, n) {
        c[i].resize(n);
        rep(j, n) {
            char cc;
            cin >> cc;
            c[i][j] = cc - '0';
        }
    }
}

vector<pair<pii, pii>> moves;

int greedy_dfs(int y, int x, vii &used, vector<pair<pii, pii>> &connect) {
    used[y][x] = true;
    int type = c[y][x];

    int res = 1;

    rep(k, 4) {
        if (moves.size() + connect.size() == 100 * k) {
            break;
        }

        REP(dist, 1, inf) {
            int ny = y + dy[k] * dist, nx = x + dx[k] * dist;

            if (not in(ny, 0, n) or not in(nx, 0, n)) {
                break;
            }

            if (used[ny][nx]) {
                break;
            }

            if (c[ny][nx] == 0) {
                continue;
            }

            if (c[ny][nx] == type) {
                connect.emplace_back(pii(y, x), pii(ny, nx));
                for (int i = min(y, ny); i <= max(y, ny); i++) {
                    for (int j = min(x, nx); j <= max(x, nx); j++) {
                        used[i][j] = true;
                    }
                }

                res += greedy_dfs(ny, nx, used, connect);
                break;
            } else {
                break;
            }
        }
    }
    return res;
}

signed main() {
    start_c = clock();

    input();

    vector<pair<pii, pii>> best_connect;
    int best_score = 0;

    rep(try_num, inf) {
        double sec = (double)(clock() - start_c) / CLOCKS_PER_SEC;
        if (sec > 2.9) {
            DEBUG(try_num);
            break;
        }

        while (true) {
            int y = rnd(n), x = rnd(n);
            int k = rnd(4);

            if (c[y][x] == 0) {
                continue;
            }
            int ny = y + dy[k], nx = x + dx[k];
            if (not in(ny, 0, n) or not in(nx, 0, n)) {
                continue;
            }
            if (c[ny][nx] != 0) {
                continue;
            }

            moves.emplace_back(pii(y, x), pii(ny, nx));
            swap(c[ny][nx], c[y][x]);
            break;
        }

        vector<pair<pii, pii>> connect;
        int score = 0;
        vii used(n, vi(n));
        rep(i, n) {
            rep(j, n) {
                if (c[i][j] != 0 && used[i][j] == 0) {
                    int sz = greedy_dfs(i, j, used, connect);
                    score += sz * (sz - 1) / 2;
                }
            }
        }
        DEBUG(score);
        DEBUG(connect.size());

        if (score > best_score) {
            best_score = score;
            best_connect = connect;
        } else {
            auto [yx, nyx] = moves.back();
            moves.pop_back();
            auto [y, x] = yx;
            auto [ny, nx] = nyx;
            swap(c[ny][nx], c[y][x]);
        }
    }

    cout << moves.size() << endl;
    for (auto [yx1, yx2] : moves) {
        cout << yx1.first << " " << yx1.second << " " << yx2.first << " " << yx2.second << endl;
    }
    cout << best_connect.size() << endl;
    for (auto [yx1, yx2] : best_connect) {
        cout << yx1.first << " " << yx1.second << " " << yx2.first << " " << yx2.second << endl;
    }
}