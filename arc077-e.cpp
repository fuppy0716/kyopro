#include "bits/stdc++.h"
using namespace std;

#define DEBUG(x) cout << #x << ": " << x << endl;
#define DEBUG_VEC(v)                                      \
  cout << #v << ":";                                      \
  for (int i = 0; i < v.size(); i++) cout << " " << v[i]; \
  cout << endl

typedef long long ll;
#define vi vector<int>
#define vl vector<ll>
#define vii vector<vector<int> >
#define vll vector<vector<ll> >
#define vs vector<string>
#define pii pair<int, int>
#define pis pair<int, string>
#define psi pair<string, int>
#define pll pair<ll, ll>
const int inf = 1000000001;
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout << setprecision(15) << fixed << p << endl;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int dx2[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy2[8] = {0, 1, 1, 1, 0, -1, -1, -1};


int main(){
  ll n, m, i, j;
  cin >> n >> m;
  vl a(n);
  for (i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
  }
  vii num(m);
  for (i = 1; i < n; i++) {
    num[a[i]].push_back(i);
  }
  vi cnt0(2 * m);
  
  for (i = 1; i < n; i++) {
    int from = a[i - 1], to = a[i];
    if (from > to) {
      to += m;
    }
    cnt0[from + 1]++;
    cnt0[to]--;
  }
  vi cnt1(2 * m);
  cnt1[0] = cnt0[0];
  for (i = 1; i < 2*m; i++) {
    cnt1[i] = cnt1[i - 1] + cnt0[i];
  }
  vi cnt(m);
  for (i = 0; i < m; i++) {
    cnt[i] = cnt1[i] + cnt1[i + m];
  }
  /*
  DEBUG_VEC(cnt);
  for (i = 0; i < m; i++) {
    for (j = 0; j < num[i].size(); j++) {
      cout << num[i][j] << " ";
    }
    cout << endl;
  }
  */
  vl dp(m);
  for (i = 1; i < n; i++) {
    dp[0] += min(1 + (a[i] + m)%m, (a[i] + m - a[i-1])%m);
  }
  ll mn = dp[0];
  for (i = 1; i < m; i++) {
    dp[i] = dp[i - 1] - cnt[i - 1];
    for (j = 0; j < num[i - 1].size(); j++) {
      int i0 = num[i - 1][j];
      dp[i] += (a[i0] + m - a[i0-1])%m - 1;
    }
    mn = min(mn, dp[i]);
  }
  //DEBUG_VEC(dp);
  cout << mn << endl;
  //cout << dp[0] << endl;
}

/*
4 6
1 5 1 4
*/
