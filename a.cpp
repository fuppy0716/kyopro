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

const int MAXN = 555555;

vl fact(MAXN);
vl rfact(MAXN);

ll mod_pow(ll x, ll p, ll M = MOD) {
    if (p < 0) {
        x = mod_pow(x, M - 2, M);
        p = -p;
    }
    x %= M;
    ll a = 1;
    while (p) {
        if (p % 2)
            a = a * x % M;
        x = x * x % M;
        p /= 2;
    }
    return a;
}

ll mod_inverse(ll a, ll M = MOD) {
    return mod_pow(a, M - 2, M);
}

void set_fact(ll n, ll M = MOD) {
    fact[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fact[i] = i * fact[i - 1] % M;
    }
    rfact[n] = mod_inverse(fact[n], M);
    for (ll i = n - 1; i >= 0; i--) {
        rfact[i] = (i + 1) * rfact[i + 1] % M;
    }
}

//http://drken1215.hatenablog.com/entry/2018/06/08/210000
//n���傫��fact���v�Z�ł��Ȃ��Ƃ��̂ق��̌v�Z���@�ɂ��ď����Ă���
ll nCr(ll n, ll r, ll M = MOD) {
    if (r > n) return 0;
    assert(fact[2] == 2);
    ll ret = fact[n];
    if (rfact[r] == 0) {
        rfact[r] = mod_inverse(fact[r], M);
    }
    ret = (ret * rfact[r]) % M;
    if (rfact[n - r] == 0) {
        rfact[n - r] = mod_inverse(fact[n - r], M);
    }
    ret = (ret * rfact[n - r]) % M;
    return ret;
}

ll nHr(ll n, ll r) {
    return nCr(n + r - 1, r);
}

signed main() {
    int n;
    cin >> n;
    vi w(n);
    rep(i, n) cin >> w[i];

    set_fact(n + 10);

    int W = 10010;
    vll dp(n + 1, vl(2 * W));
    dp[0][W] = 1;

    vll ndp(n + 1, vl(2 * W));
    rep(i, n) {
        rep(j, n + 1) rep(k, 2 * W) ndp[j][k] = 0;
        int x = w[i];

        rep(l, n) {
            rep(j, 2 * W) {
                if (dp[l][j] == 0) continue;

                (ndp[l][j - x] += dp[l][j]) %= MOD;
                (ndp[l + 1][j + x] += dp[l][j]) %= MOD;
            }
        }
        swap(dp, ndp);
    }

    ll ans = 0;
    rep(i, n + 1) {
        // DEBUG(pii(i, dp[i][W]));
        ans += fact[i] * fact[n - i] % MOD * dp[i][W] % MOD;
    }
    cout << ans % MOD << endl;
}