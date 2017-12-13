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
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
  int t, i, j;
  cin >> t;
  int a, b, c, d, e;
  cin >> a >> b >> c >> d >> e;
  vll dp(t + 1, vl(30000));
  dp[0][15000] = 1;
  for (i = 0; i < t; i++) {
    for (j = 0; j < 30000; j++) {
      if (dp[i][j]) {
	dp[i + 1][j + a] += dp[i][j];
	dp[i + 1][j - a] += dp[i][j];
	dp[i + 1][j + b] += dp[i][j];
	dp[i + 1][j - b] += dp[i][j];
	dp[i + 1][j + c] += dp[i][j];
	dp[i + 1][j - c] += dp[i][j];
	dp[i + 1][j + a] %= MOD;
	dp[i + 1][j - a] %= MOD;
	dp[i + 1][j + b] %= MOD;
	dp[i + 1][j - b] %= MOD;
	dp[i + 1][j + c] %= MOD;
	dp[i + 1][j - c] %= MOD;
      }
    }
  }
  ll ans = 0;
  for (i = d + 15000; i <= e + 15000; i++) {
    ans += dp[t][i];
    ans %= MOD;
  }
  cout << ans << endl;
}
