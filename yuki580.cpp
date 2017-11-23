#include "bits/stdc++.h"
using namespace std;

#define DEBUG(x) cout << #x << ": " << x << endl;
#define DEBUG_VEC(v) cout << #v << ":";for (int i = 0; i < v.size(); i++) cout << " " << v[i];cout << endl;

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
  int n, V, i, j;
  scanf("%d%d",&n, &V);
  vector<pii> a(V);
  for (i = 0; i < V; i++) {
    int d,hh,mm,o,hho,mmo;
    scanf("%d %d:%d %d %d:%d",&d,&hh,&mm,&o,&hho,&mmo);
    int s, g;
    s = (d - 2)*24*60 + hh*60 + mm;
    g = (o - 2)*24*60 + hho*60 + mmo;
    a[i] = pii(s, g);
  }
  sort(a.begin(), a.end());
  int cnt = 0;
  int ans = 0;
  vector<pii> f(n);
  /*
  for (j = 0; j < V; j++) {
    printf("(%d, %d)\n", a[j].first, a[j].second);
  }
  */
  for (i = 0; i < V; i++) {
    for (j = 0; j < cnt; j++) {
      if (a[i].first > f[j].second) {
	ans++;
	f[j] = a[i];
	break;
      }
    }
    if (j == cnt) {
      if (cnt < n) {
	f[cnt++] = a[i];
      }
      else {
	int slow = -1, slowi = -1;
	for (j = 0; j < cnt; j++) {
	  if (slow < f[j].second) {
	    slow = f[j].second;
	    slowi = j;
	  }
	}
	if (slow > a[i].second) {
	  f[slowi] = a[i];
	}
      }
    }
    /*
    DEBUG(ans);
    for (j = 0; j < cnt; j++) {
      printf("(%d, %d) ", f[j].first, f[j].second);
    }
    cout << endl;
    */
  }
  cout<< ans + cnt <<endl;
      
      
}

/*
1 3
3 10:00 3 10:00
3 10:00 3 10:00
3 10:01 3 10:02

2 7
3 12:30 4 15:30
3 16:30 3 16:30
3 16:31 4 15:29
4 15:30 7 15:30
2 02:00 3 15:29
3 15:10 4 15:29
3 12:47 4 14:27

3 11
3 12:30 4 15:30
4 15:31 5 16:20
5 16:21 6 17:30
3 12:30 4 15:30
4 17:30 6 03:30
7 12:10 8 23:59
2 14:40 4 15:30
5 16:40 7 12:20
8 00:00 8 17:54
8 17:54 8 17:55
2 12:00 7 03:30

*/

