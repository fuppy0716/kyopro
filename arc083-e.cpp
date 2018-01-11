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
#define pll pair<ll, ll>
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define N 1010

int n;
vi p(N), childnum(N);
vii child(N, vi());
vi x(N);
vector<pii> bw(N);


bool solve(int k) {
  if (child[k].size() == 0) {
    bw[k] = pii(x[k], 0);
    return true;
  }
  for (int i = 0; i < child[k].size(); i++) {
    if (!solve(child[k][i])) {
      return false;
    }
  }
  vector<vector<bool> > dp(child[k].size() + 1, vector<bool>(5010, false));
  dp[0][0] = true;
  for (int i = 0; i < child[k].size(); i++) {
    for (int j = 5005; j >= 0; j--) {
      if (dp[i][j]) {
	dp[i + 1][min(5009, j + bw[child[k][i]].first)] = true;
	dp[i + 1][min(5009, j + bw[child[k][i]].second)] = true;
      }
    }
  }
  int sum = 0;
  for (int i = 0; i < child[k].size(); i++) {
    sum += bw[child[k][i]].first + bw[child[k][i]].second;
  }
  int m = inf;
  for (int i = 0; i <= 5000; i++) {
    if (dp[child[k].size()][i]) {
      int aikata = sum - i;
      if (i <= x[k]) {
	m = min(m, aikata);
      }
      if (aikata <= x[k]) {
	m = min(m, i);
      }
    }
  }
  if (m == inf) {
    return false;
  }
  else {
    bw[k] = pii(x[k], m);
    return true;
  }
      
  
}


int main () {
  int i;
  cin >> n;
  for (i = 1; i < n; i++) {
    cin >> p[i];
    p[i]--;
    child[p[i]].push_back(i);
    childnum[p[i]]++;
  }
  for (i = 0; i < n; i++) {
    cin >> x[i];
  }
  if(solve(0)) {
    cout << "POSSIBLE" << endl;
  }
  else {
    cout << "IMPOSSIBLE" << endl;
  }
}
