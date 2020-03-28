#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define DEBUG(x) cerr<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cerr<<#v<<":";for(int i=0;i<v.size();i++) cerr<<" "<<v[i]; cerr<<endl
#define DEBUG_MAT(v) cerr<<#v<<endl;for(int i=0;i<v.size();i++){for(int j=0;j<v[i].size();j++) {cerr<<v[i][j]<<" ";}cerr<<endl;}


typedef long long ll;
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
const ll MOD = 1000000007;
//const ll MOD = 998244353;
const double pi = 3.14159265358979323846;
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0, -1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };
#define fio() cin.tie(0); ios::sync_with_stdio(false);
//#define mp make_pair


#define N 1010
vii G(N); //グラフの隣接リスト表現

void lowlink_dfs(int now, int par, int k, vector<bool> &used, vi &ord, vi &lowlink, vii &ch) {
  used[now] = true;
  ord[now] = lowlink[now] = k++;
  for (int i = 0; i < G[now].size(); i++) {
    int v = G[now][i];
    if (v == par) continue;
    if (!used[v]) {
      ch[now].push_back(v);
      lowlink_dfs(v, now, k, used, ord, lowlink, ch);
      lowlink[now] = min(lowlink[now], lowlink[v]);
    }
    else {
      lowlink[now] = min(lowlink[now], ord[v]);
    }
  }
  return;
}

vector<pii> bridge(int n) {
  vector<bool> used(n);
  vi ord(n), lowlink(n);
  vii ch(n);
  
  int k = 0;
  rep (i, n) {
    if (!used[i])
      lowlink_dfs(i, -1, k, used, ord, lowlink, ch);
  }

  vector<pii> bri;
  rep (u, n) {
    for (int v: G[u]) {
      if (ord[u] > ord[v]) continue;
      if (ord[u] < lowlink[v]) 
        bri.push_back(pii(u, v));
    }
  }
  return bri;
}

vector<int> kansetsu(int n) {
  vector<bool> used(n);
  vi ord(n), lowlink(n);
  vii ch(n);

  vector<bool> is_root(n);
  int k = 0;
  rep (i, n) {
    if (!used[i]) {
      is_root[i] = true;
      lowlink_dfs(i, -1, k, used, ord, lowlink, ch);
    }
  }

  vi kan;
  rep (u, n) {
    if (is_root[u]) {
      if (ch[u].size() >= 2) {
        kan.push_back(u);
      }
    }
    else {
      for (int v: ch[u]) {
        if (ord[u] <= lowlink[v]) {
          kan.push_back(u);
          break;
        }
      }
    }
  }
  return kan;
}
