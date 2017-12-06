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

int main() {
  ll n, k, q;
  cin >> n >> k >> q;
  vector<char> a(q);
  vl b(q), c(q);
  int i, j;
  vector<pii> tate(n, pii(-1, 0)), yoko(n, pii(-1, 0));
  for (i = 0; i < q; i++) {
    cin >> a[i] >> b[i] >> c[i];
    b[i]--; c[i]--;
    if (a[i] == 'R') {
      yoko[b[i]].first = i;
    }
    else {
      tate[b[i]].first = i;
    }
  }
  sort(yoko.begin(), yoko.end());
  sort(tate.begin(), tate.end());
  int yokoi = n-1, tatei = n-1;
  while (yokoi >= 0 || tatei >= 0) {
    if (yokoi < 0) {
      tate[tatei].second = (n - 1 - yokoi);
      tatei--;
    }
    else if (tatei < 0) {
      yoko[yokoi].second = (n - 1 - tatei);
      yokoi--;
    }
    else if (yoko[yokoi].first < 0 && tate[tatei].first < 0) {
      yoko[yokoi].second = (n - 1 - tatei);
      yokoi--;
    }
    else {
      if (yoko[yokoi].first > tate[tatei].first) {
	yoko[yokoi].second = (n - 1) - tatei;
	yokoi--;
      }
      else {
	tate[tatei].second = (n - 1) - yokoi;
	tatei--;
      }
    }
  }
  /*
  for (i = 0; i < n; i++) {
    cout << yoko[i].first << " " << yoko[i].second << endl;
  }
  cout << endl;
  for (i = 0; i < n; i++) {
    cout << tate[i].first << " " << tate[i].second << endl;
  }
  cout << endl;
  */
  vl color(k);
  for (i = 0; i < n; i++) {
    if (yoko[i].first < 0) {
      color[0] += n - yoko[i].second;
    }
    else {
      color[c[yoko[i].first]] += n - yoko[i].second;
    }
  }
  for (i = 0; i < n; i++) {
    if (tate[i].first < 0) {
      color[0] += n - tate[i].second;
    }
    else {
      color[c[tate[i].first]] += n - tate[i].second;
    }
  }
  for (i = 0; i < k; i++) {
    cout << color[i] << endl;
  }
  return 0;
}
  
/*
3 4 6
C 1 2
C 2 3
R 2 1
C 3 4
R 3 3
C 2 1

1 5 2
R 1 4
R 1 4

100000 2 1
R 12345 2
*/
