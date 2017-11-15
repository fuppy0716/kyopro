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

#define pcc pair<char, char>
#define N 30
#define M 2010

vector< vector<bool> > G(N, vector<bool>(N));

void kahn() {
  vector<bool> used(26, false);
  string ans;
  int u, v;
  bool ok = true;
  for (int i = 0; i < 26; i++) {
    for (u = 0; u < 26; u++) {
      if(used[u]) continue;
      ok = true;
      for (v = 0; v < 26; v++) {
	if (G[v][u]) ok = false;
      }
      if(ok) break;
    }
    if(!ok) {
      cout << -1 << endl;
      return;
    }
    used[u] = true;
    ans.push_back((char)('a' + u));
    for (v = 0; v < 26; v++) {
      G[u][v] = false;
    }
  }
  cout << ans << endl;
}

int main() {
  int n, i, j;
  cin >> n;
  vs a(n), b(n);
  
  for (i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < min(a[i].size(),b[i].size()); j++) {
      if (a[i][j] != b[i][j]) {
	G[a[i][j] - 'a'][b[i][j] - 'a'] = true;
	break;
      }
    }
    if (j == b[i].size()) {
      cout << -1 << endl;
      return 0;
    }
  }
  kahn();
}
