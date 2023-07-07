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

vi can;
using lll = __int128_t;

bool check(vi a) {

    lll bo = 1;
    rep(i, a.size()) {
        bo *= a[i];
    }

    lll s = 0;
    rep(i, a.size()) {
        s += bo / a[i];
    }
    return s == bo;
}

constexpr int N = 68;
vi par(N);

bool dfs(vi &a, int n, double s, vi &used) {
    if (s > 1.1) {
        return false;
    }

    if (n == 0) {
        // double s = 0;
        // rep(i, a.size()) {
        //     s += 1.0 / a[i];
        // }
        // DEBUG(s);
        if (check(a)) {
            rep(i, a.size()) {
                cout << a[i] << ", ";
            }
            cout << endl;
            // DEBUG_VEC(a);
            return true;
        }
        return false;
    }

    int pre = 1;
    if (a.size() > 0) {
        pre = a.back();
    }
    for (int x = pre + 2; x < 68; x += 2) {
        // for (int x = pre + 1; x < 60; x++) {
        // if (used[par[x]]) {
        //     continue;
        // }
        a.push_back(x);
        double ns = s + 1.0 / x;
        // used[par[x]] = true;
        bool ret = dfs(a, n - 1, ns, used);
        if (ret) {
            return true;
        }
        // used[par[x]] = false;
        a.pop_back();
    }
    return false;
}

void solve(int n) {
    vi a;
    vi used(N);
    bool ret = dfs(a, n, 0.0, used);
    DEBUG(ret);
}

signed main() {
    for (int n = 3; n <= 43; n += 2) {
        solve(n);
    }

    for (int x = 1; x < N; x++) {
        int y = x;
        while (y % 2 == 0) {
            y /= 2;
        }
        par[x] = y;
    }

    int t = 1;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        solve(n);
    }
}
