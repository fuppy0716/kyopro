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
  int n, i, j;
  cin >> n;
  vl a(n);
  //vector<pii> b(n);
  vl b(n);
  for (i = 0; i < n; i++) {
    cin >> a[i];
    //b[i].first = a[i];
    //b[i].second = i;
    b[i] = a[i];
  }
  sort(b.begin(), b.end());
  int pre = 0;
  int now = 0;
  for (i = 0; i < n; i++) {
    if (pre >= a[i]) {
      cout << 0 << endl;
      continue;
    }
    ll cnt = 0;
    while (b[now] < a[i]) {
      cnt += (b[now] - pre);
      now++;
    }
    cnt += (a[i] - pre) * (n - now);
    cout << cnt << endl;
    pre = a[i];
  }  
}

/*
2
1 2


10
1 2 1 3 2 4 2 5 8 1
*/
