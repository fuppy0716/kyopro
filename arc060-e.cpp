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

int main() {
  int n, i0, i, j;
  scanf("%d", &n);
  vl x(n);
  for (i0 = 0; i0 < n; i0++) {
    scanf("%lld", &x[i0]);
  }
  ll l;
  int q;
  scanf("%lld", &l);

  vii dp(100, vi(n, inf));
  for (i = 0; i < n; i++) {
    auto itr = lower_bound(x.begin(), x.end(), x[i] + l);
    if (*(itr) == x[i] + l) {
      dp[0][i] = itr - x.begin();
    }
    else {
      dp[0][i] = itr - x.begin() - 1;
    }
  }
  for (i = 0; i < 99; i++) {
    for (j = 0; j < n; j++) {
      if (dp[i][j] == n - 1) {
	dp[i + 1][j] = n - 1;
	continue;
      }
      dp[i + 1][j] = dp[i][dp[i][j]];
    }
    if (dp[i + 1][0] == n - 1) {
      break;
    }
  }
  /*
  for (i = 0; i < 5; i++) {
    for (j = 0; j < n; j++) {
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }
  */
  scanf("%d", &q);
  for (i0 = 0; i0 < q; i0++) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > b) {
      swap(a, b);
    }
    a--; b--;
    int now = a;
    ll cnt = 0;
    while (true) {
      //cout << now << " " << cnt << endl;
      for (i = 99; i >= 0; i--) {
	if (dp[i][now] < b) {
	  cnt += pow(2, i);
	  now = dp[i][now];
	  break;
	}
      }
      if (i == -1) {
	cnt++;
	cout << cnt << endl;
	break;
      }
    }
  }
}

/*
9
1 3 6 13 15 18 19 29 31
10
4
1 8
7 3
6 7
8 5
*/
