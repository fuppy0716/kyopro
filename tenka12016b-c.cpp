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
  int n, p1, p2;
  scanf("%d %d/%d",&n,&p1,&p2);
  double p = (double)p1/p2;
  vii a(n, vi(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d",&a[i][j]);
    }
  }
  vi win(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i][j]) {
	win[i]++;
      }
    }
  }
  vi jun;
  for (int i = n; i >= 0; i--) {
    for (int j = 0; j < n; j++) {
      if (win[j] == i) {
	jun.push_back(j);
      }
    }
  }
  //DEBUG(p);
  //DEBUG_VEC(win);
  //DEBUG_VEC(jun);
  vector< vector<double> > dpp(n, vector<double>(n));
  for (int i = 0; i < n; i++) {
    dpp[i][0] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j)
	continue;
      for (int k = n - 2; k >= 0; k--) {
	if (a[i][j]) {
	  dpp[i][k + 1] += dpp[i][k] * p;
	  dpp[i][k] = dpp[i][k] * (1 - p);
	}
	else {
	  dpp[i][k + 1] += dpp[i][k] * (1 - p);
	  dpp[i][k] = dpp[i][k] * p;
	}
      }
    }
  }
  /*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << dpp[i][j] << " ";
    }
    cout << endl;
  }
  */
  
  vector< vector<double> > dpj(n, vector<double>(n));
  for (int i = 0; i < n; i++) {
    dpj[0][i] = dpp[jun[0]][i];
  }
  int pre = jun[0];
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n; j++) {
      if (pre < jun[i + 1]) { //同率よし
	//cout << "aaa"<< endl;
	for (int k = 0; k <= j; k++) {
	  dpj[i + 1][k] += dpj[i][j] * dpp[jun[i + 1]][k];
	}
      }
      else {
	//cout << "bbb" << endl;
	for (int k = 0; k < j; k++) {
	  dpj[i + 1][k] += dpj[i][j] * dpp[jun[i + 1]][k];
	}
      }
    }
    pre = jun[i + 1];
  }
  /*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << dpj[i][j] << " ";
    }
    cout << endl;
  }
  */
  double ans = 0;
  for (int i = 0; i < n; i++) {
    ans += dpj[n - 1][i];
  }
  Sp(ans);
	
}

/*
2 2/3
0 1
0 0

2 4/6
0 0
1 0

5 0/1
0 1 1 1 1
0 0 1 1 1
0 0 0 1 1
0 0 0 0 1
0 0 0 0 0

5 4/7
0 1 0 0 1
0 0 1 1 0
1 0 0 0 0
1 0 1 0 0
0 1 1 1 0
*/
