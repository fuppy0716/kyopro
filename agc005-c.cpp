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
  int n, i, j;
  cin >> n;
  int m = inf, M = -1;
  vi num(101);
  for (i = 0; i < n; i++) {
    int a;
    cin >> a;
    m = min(m, a);
    M = max(M, a);
    num[a]++;
  }
  bool flag = false;
  if (num[m] > 2) {
    flag = false;
  }
  else if (num[m] == 2) {
    if (M == 2*m - 1) {
      for (i = m + 1; i <= M; i++) {
	if (num[i] < 2) {
	  cout << "Impossible" << endl;
	  return 0;
	}
      }
      flag = true;
    }
  }
  else if (num[m] == 1) {
    if (M == 2*m) {
      for (i = m + 1; i <= M; i++) {
	if (num[i] < 2) {
	  cout << "Impossible" << endl;
	  return 0;
	}
      }
      flag = true;
    }
  }
  if (flag) {
    cout << "Possible" << endl;
  }
  else {
    cout << "Impossible" << endl;
  }
}

