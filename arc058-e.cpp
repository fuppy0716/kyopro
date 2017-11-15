#include <bits/stdc++.h>
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
const int inf = 1000000001;
const ll INF = 1e18;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout << setprecision(15) << fixed << p << endl;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int dx2[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy2[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int n, x, y, z;

ll mod_pow(ll x, ll p, ll M) {
  ll a = 1;
  while (p) {
    if (p % 2) {
      a = a*x%MOD;
    }
    x = x*x%MOD;
    p /= 2;
  }
  return a;
}

bool safe(int a, int b) {
  a <<= 1;
  a += 1;
  a <<= (b - 1);
  bool flag = true;
  int c = 1;
  c <<= (z - 1);
  if (!(c & a)) {
    flag = false;
  }
  c <<= y;
  if (!(c & a)) {
    flag = false;
  }
  c <<= x;
  if (!(c & a)) {
    flag = false;
  }
  return !flag;
}
  

int main() {
  int i, j, k;
  cin >> n >> x >> y >> z;
  ll m = 1 << (x + y + z);
  vll dp(n + 1, vl(m));
  dp[0][0] = 1;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      for (k = 1; k <= 10; k++) {
	if (safe(j, k)) {
	  int jn = j;
	  jn <<= 1;
	  jn += 1;
	  jn <<= (k - 1);
	  jn %= (1 << (x + y + z));
	  dp[i+1][jn] = (dp[i+1][jn] + dp[i][j]) % MOD;
	}
      }
    }
  }
  /*
  for (i = 0; i <= n; i++) {
    for (j = 0; j < m; j++) {
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }
  */
  ll ans = 0;
  
  for (j = 0; j < m; j++) {
    ans = (ans + dp[n][j]) % MOD;
  }
  ans = (mod_pow(10, n, MOD) - ans) % MOD;
  while (ans < 0) {
    ans += MOD;
  }
  cout << ans << endl;
}
  
