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
#define pll pair<ll,ll>
const int inf = 1000000001;
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
  int n, m, k, i, j;
  cin >> n >> m >> k;
  vl a(n), b(m);
  for (i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (i = 0; i < m; i++) {
    cin >> b[i];
  }
  sort(a.begin(), a.end(), greater<ll>());
  sort(b.begin(), b.end(), greater<ll>());
  if (n > m) {
    swap(a, b);
    swap(n, m);
  }
  ll left = -1, right = inf;
  //DEBUG_VEC(a);
  //DEBUG_VEC(b);
  while (right - left > 1) {
    ll x = (left + right) / 2;
    int cnt = 0;
    int j = 0;
    for (i = 0; i < n; i++) {
      while (b[j] - a[i] > x && j < m) {
	//printf("i:%d j:%d a[i]:%lld b[j]:%lld\n",i,j,a[i],b[j]);
	j++;
      }
      if (j == m) {
	break;
      }
      //printf("aaai:%d j:%d a[i]:%lld b[j]:%lld",i,j,a[i],b[j]);
      if (abs(b[j] - a[i]) <= x) {
	cnt++;
	j++;
      }
    }
    //printf("cnt:%d",cnt);
    if (cnt >= k) {
      right = x;
    }
    else {
      left = x;
    }
    //cout << endl;
  }
  cout << right << endl;
}
    
/*
6 5 3
15 7 14 3 14 11
20 18 15 18 17
 */
