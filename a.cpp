#include <bits/stdc++.h>
 
using namespace std;
 
#define DEBUG(x) cerr<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cerr<<#v<<":";for(int i=0;i<v.size();i++) cerr<<" "<<v[i]; cerr<<endl;
#define DEBUG_MAT(v) cerr<<#v<<endl;for(int i=0;i<v.size();i++){for(int j=0;j<v[i].size();j++) {cerr<<v[i][j]<<" ";}cerr<<endl;}
typedef long long ll;
#define int ll
 
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
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define rrep(i,n) for(int i=(n)-1;i>=0;i--)
#define rrep1(i,n) for(int i=(n);i>0;i--)
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

const int MAXN = 555555;

vl fact(MAXN);
vl rfact(MAXN);

ll mod_pow(ll x, ll p, ll M = MOD) {
  if (p < 0) {
    x = mod_pow(x, M - 2, M);
    p = -p;
  }
  ll a = 1;
  while (p) {
    if (p % 2)
      a = a*x%M;
    x = x*x%M;
    p /= 2;
  }
  return a;
}

ll mod_inverse(ll a, ll M = MOD) {
  return mod_pow(a, M - 2, M);
}

void set_fact(ll n, ll M = MOD) {
  fact[0] = fact[1] = rfact[0] = rfact[1] = 1;
  for (ll i = 2; i <= n; i++) {
    fact[i] = i * fact[i - 1] % M;
    // rfact[i] = mod_inverse(fact[i], M);
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
  ret = (ret*rfact[r]) % M;
  if (rfact[n - r] == 0) {
    rfact[n - r] = mod_inverse(fact[n - r], M);
  }
  ret = (ret*rfact[n - r]) % M;
  return ret;
}

ll nHr(ll n, ll r) {
  return nCr(n+r-1, r);
}

ll gcd(ll a, ll b) {
  if (b > a) {
    swap(a, b);
  }
  ll r = a%b;
  while (r != 0) {
    a = b;
    b = r;
    r = a%b;
  }
  return b;
}

ll lcm(ll a, ll b) {
  return (a / gcd(a, b))*b;
}

ll solve(int h, int w) {
    if (h > w) swap(h, w);

    ll ans = 0;
    ans = mod_pow(2, h);
    ans += mod_pow(2, w);
    ans -= 1;
    ll g = gcd(h, w);
    ans += mod_pow(2, g);
    ans -= 2;
    ans = (ans % MOD + MOD) % MOD;
    return ans;
}


signed main() {
    fio();
    ll h, w, t;
    cin >> h >> w >> t;
    ll hh = h / gcd(h, t);
    ll ww = w / gcd(w, t);
    ll ans = solve(hh, ww);
    ans = mod_pow(ans, (h * w) / (hh * ww));

    cout << ans << endl;
}