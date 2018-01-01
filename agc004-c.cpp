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
  int h, w, i, j;
  cin >> h >> w;
  vs a(h);
  for (i = 0; i < h; i++) {
    cin >> a[i];
  }
  vs red(h, string(w, '.'));
  vs blue(h, string(w, '.'));
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
	red[i][j] = '#';
      }
      else {
	if (i % 4 == 2) {
	  if (j != 1) {
	    red[i][j] = '#';
	  }
	}
	else if (i % 4 == 0) {
	  if (j != w - 2) {
	    red[i][j] = '#';
	  }
	}
      }
    }
  }
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
	continue;
      }
      else {
	if (i % 4 == 2) {
	  if (j == 1) {
	    blue[i][j] = '#';
	  }
	}
	else if (i % 4 == 0) {
	  if (j == w - 2) {
	    blue[i][j] = '#';
	  }
	}
	else {
	  blue[i][j] = '#';
	}
      }
    }
  }
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      if (a[i][j] == '#') {
	red[i][j] = blue[i][j] = '#';
      }
    }
  }
  for (i = 0; i < h; i++) {
    cout << red[i] << endl;
  }
  cout << endl;
  for (i = 0; i < h; i++) {
    cout << blue[i] << endl;
  }
      
}

