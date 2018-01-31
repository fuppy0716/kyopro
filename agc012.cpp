#include "bits/stdc++.h"
using namespace std;

#define DEBUG(x) cout<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cout<<#v<<":";for(int i=0;i<v.size();i++) cout<<" "<<v[i]; cout<<endl

typedef long long ll;
#define vi vector<int>
#define vl vector<ll>
#define vii vector< vector<int> >
#define vll vector< vector<ll> >
#define vs vector<string>
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define int ll

ll MAXM = 200100;
vl fact(MAXM);
vl C(MAXM);

ll mod_pow(ll x, ll p, ll M) {
  ll a = 1;
  while (p) {
    if (p % 2)
      a = a*x%MOD;
    x = x*x%MOD;
    p /= 2;
  }
  return a;
}

ll mod_inverse(ll a, ll m) {
  return mod_pow(a, m - 2, m);
}

ll nCr(ll n, ll r) {
  ll ret = fact[n];
  ret = (ret*mod_inverse(fact[r], MOD)) % MOD;
  ret = (ret*mod_inverse(fact[n - r], MOD)) % MOD;
  return ret;
}


#define N 200010
vi par(N); //親
vi ran(N); //木の深さ
vi num(N);

//n要素で初期化
void init(int n){
  int i;
  num.resize(n);
  for (i = 0; i < n; i++){
    par[i]=i;
    ran[i]=0;
    num[i]=1;
  }
}

//木の根を求める
int find(int x){
  if(par[x]==x){
    return x;
  }else{
    return par[x]=find(par[x]);
  }
}

//xとyの属する集合を併合
void unite(int x,int y){
  x=find(x);
  y=find(y);
  int numsum = num[x] + num[y];
  if(x==y){
    return;
  }
  if(ran[x]<ran[y]){
    par[x]=y;
  }else{
    par[y]=x;
    if(ran[x]==ran[y]){
      ran[x]++;
    }
  }
  num[x] = num[y] = numsum;
}

//xとyが同じ集合に属するか否か
bool same(int x,int y){
  return find(x)==find(y);
}


signed main() {
  int n, x, y, i, j;
  cin >> n >> x >> y;

  init(n);

  vector<pii> cw(n);
  for (i = 0; i < n; i++) {
    cin >> cw[i].first >> cw[i].second;
  }
  sort(cw.begin(), cw.end());

  int precolor = -1;
  vector<vector<pair<pii, int> > > cw2;
  j = -1;
  for (i = 0; i < n; i++) {
    if (cw[i].first != precolor) {
      cw2.push_back(vector<pair<pii,int> >(1, make_pair(cw[i], i)));
      precolor = cw[i].first;
      j++;
    }
    else {
      cw2[j].push_back(make_pair(cw[i], i));
    }
  }

  if (cw2.size() == 1) {
    cout << 1 << endl;
    return 0;
  }

  /*
  for (i = 0; i < cw2.size(); i++) {
    for (j = 0; j < cw2[i].size(); j++) {
      printf("(%lld, %lld, %lld), ", cw2[i][j].first.first, cw2[i][j].first.second, cw2[i][j].second);
    }
    cout << endl;
  }
  //*/

  for (i = 0; i < cw2.size(); i++) {
    for (j = 1; j < cw2[i].size(); j++) {
      if (cw2[i][0].first.second + cw2[i][j].first.second <= x) {
	unite(cw2[i][0].second, cw2[i][j].second);
      }
      else {
	break;
      }
    }
  }


  int minw = inf;
  int mini;

  for (i = 0; i < cw2.size(); i++) {
    if (minw > cw2[i][0].first.second) {
      minw = cw2[i][0].first.second;
      mini = i;
    }
  }

  int minw2 = inf;
  int mini2;

  for (i = 0; i < cw2.size(); i++) {
    if (i == mini) {
      continue;
    }
    if (minw2 > cw2[i][0].first.second) {
      minw2 = cw2[i][0].first.second;
      mini2 = i;
    }
  }


  for (i = 0; i < cw2.size(); i++) {
    if (i == mini) {
      for (j = 0; j < cw2[i].size(); j++) {
	if (cw2[i][j].first.second + cw2[mini2][0].first.second <= y) {
	  unite(cw2[i][j].second, cw2[mini2][0].second);
	}
	else {
	  break;
	}
      }
    }
    else {
      for (j = 0; j < cw2[i].size(); j++) {
	if (cw2[i][j].first.second + cw2[mini][0].first.second <= y) {
	  unite(cw2[i][j].second, cw2[mini][0].second);
	}
	else {
	  break;
	}
      }
    }
  }

  vi colornum(cw2.size(), 0);
  for (i = 0; i < cw2.size(); i++) {
    for (j = 0; j < cw2[i].size(); j++) {
      if (same(cw2[i][j].second ,cw2[mini][0].second)) {
	colornum[i]++;
      }
    }
  }

  /*
  for (i = 0; i < colornum.size(); i++) {
  cout << colornum[i] << endl;
  }
  //*/

  ll M = 0;
  for (i = 0; i < colornum.size(); i++) {
    M += colornum[i];
  }

  fact[0] = 1;
  for (i = 1; i <= M; i++) {
    fact[i] = fact[i - 1] * i % MOD;
  }
  //DEBUG(M);
  ll ans = 1;
  for (i = 0; i < colornum.size(); i++) {
    if (colornum[i] == 0) {
      continue;
    }
    ans = ans * nCr(M, colornum[i]) % MOD;
    M -= colornum[i];
  }

  cout << ans << endl;
}

