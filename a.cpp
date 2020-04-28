#include <bits/stdc++.h>
 
using namespace std;
 
#define DEBUG(x) cerr<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cerr<<#v<<":";for(int i=0;i<v.size();i++) cerr<<" "<<v[i]; cerr<<endl;
#define DEBUG_MAT(v) cerr<<#v<<endl;for(int i=0;i<v.size();i++){for(int j=0;j<v[i].size();j++) {cerr<<v[i][j]<<" ";}cerr<<endl;}
typedef long long ll;
// #define int ll
 
#define vi vector<int>
#define vl vector<ll>
#define vii vector< vector<int> >
#define vll vector< vector<ll> >
#define vs vector<string>
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define pll pair<ll,ll>
template<class S, class T> pair<S, T> operator+(const pair<S, T> &s, const pair<S, T> &t) { return pair<S, T>(s.first + t.first, s.second + t.second); }
template<class S, class T> pair<S, T> operator-(const pair<S, T> &s, const pair<S, T> &t) { return pair<S, T>(s.first - t.first, s.second - t.second); }
template<class S, class T> ostream& operator<<(ostream& os, pair<S, T> p) { os << "(" << p.first << ", " << p.second << ")"; return os; }
#define X first
#define Y second
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define rrep(i,n) for(int i=(int)(n)-1;i>=0;i--)
#define rrep1(i,n) for(int i=(int)(n);i>0;i--)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define in(x, a, b) (a <= x && x < b)
#define all(c) c.begin(),c.end()
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a = b; return 1; } return 0; }
#define UNIQUE(v) v.erase(std::unique(v.begin(), v.end()), v.end());
const ll inf = 1000000001;
const ll INF = (ll)1e18 + 1;
const long double pi = 3.1415926535897932384626433832795028841971L;
#define Sp(p) cout<<setprecision(25)<< fixed<<p<<endl;
//int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
//int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };
vi dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
vi dx2 = { 1,1,0,-1,-1,-1,0,1 }, dy2 = { 0,1,1,1,0,-1,-1,-1 };
#define fio() cin.tie(0); ios::sync_with_stdio(false);
const ll MOD = 1000000007;
//const ll MOD = 998244353;
// #define mp make_pair
//#define endl '\n'


using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

template <class Uint, class BinOp>
bool is_prime_impl(const Uint &n, const Uint *witness, BinOp modmul) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    const Uint m = n - 1, d = m / (m & -m);
    auto modpow = [&](Uint a, Uint b) {
        Uint res = 1;
        for (; b; b /= 2) {
            if (b & 1) res = modmul(res, a);
            a = modmul(a, a);
        }
        return res;
    };
    auto suspect = [&](Uint a, Uint t) {
        a = modpow(a, t);
        while (t != n - 1 && a != 1 && a != n - 1) {
            a = modmul(a, a);
            t = modmul(t, 2);
        }
        return a == n - 1 || t % 2 == 1;
    };
    for (const Uint *w = witness; *w; w++) {
        if (*w % n != 0 && !suspect(*w, d)) return false;
    }
    return true;
}

bool is_prime(const u128 &n) {
    assert(n < 1ULL << 63);
    if (n < 1ULL << 32) {
        // n < 2^32
        constexpr u64 witness[] = {2, 7, 61, 0};
        auto modmul = [&](u64 a, u64 b) { return a * b % n; };
        return is_prime_impl<u64>(n, witness, modmul);
    } 
    else {
        // n < 2^63
        constexpr u128 witness[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};
        // if u128 is available
        auto modmul = [&](u128 a, u128 b) { return a * b % n; };
        return is_prime_impl<u128>(n, witness, modmul);
    }
}


signed main() {
    int q;
    cin >> q;
    while (q--) {
        ll x;
        cin >> x;
        
        cout << x << " " << (int)is_prime(x) << endl;
    }
}