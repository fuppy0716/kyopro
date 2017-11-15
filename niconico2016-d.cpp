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

class Cmp {
public:
  bool operator() (pii a, pii b) {
    if (a.first - a.second < b.first - b.second) {
      return false;
    }
    else {
      return true;
    }
  }
};

int main() {
  int n, m, i, j;
  cin >> n >> m;
  if (m > n) {
    m = n;
  }
  vector<pii> z(n);
  for (i = 0; i < n; i++) {
    int x,y;
    cin >> x >> y;
    z[i] = pii(x, y);
  }
  priority_queue<pii, vector<pii>, Cmp> pq;
  /*
  for (i = 0; i < n; i++) {
    pq.push(z[i]);
  }
  for (i = 0; i < n; i++) {
    pii a = pq.top();
    cout << a.first << " " << a.second << endl;
    pq.pop();
  }
  */
  int ans = 0;
  int cnt = 0;
  for (i = 0; i < m; i++) {
    cnt += z[i].first;
    pq.push(z[i]);
  }
  ans = cnt;
  for (i = m; i < n; i++) {
    pii tmp = pq.top();
    pq.pop();
    cnt = cnt - tmp.first + tmp.second;
    cnt += z[i].first;
    pq.push(z[i]);
    ans = max(ans, cnt);
  }
  cout << ans << endl;
  
}
