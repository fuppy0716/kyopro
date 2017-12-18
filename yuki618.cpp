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
#define pll pair<ll, ll>
#define pis pair<int,string>
#define psi pair<string,int>
const int inf = 1000000001;
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

const ll none = -200000000000000;

int main() {
  int q, i, j;
  scanf("%d", &q);
  int block = sqrt(q);
  vector<vector<pll> > lab;
  lab.push_back(vector<pll>());
  vl add;
  int num = 0;
  //DEBUG(block)
  ll pre = 0;
  for (int unko = 0; unko < q; unko++) {
    int t, x;
    scanf("%d%d", &t, &x);
    if (t == 1) {
      lab[num / block].push_back(pll(x, num));
      if (lab[num / block].size() == block) {
	lab.push_back(vector<pll>());
	add.push_back(0);
      }
      sort(lab[num / block].begin(), lab[num / block].end());
      num++;
    }
    else if (t == 2) {
      x--;
      i = x / block;
      for (j = 0; j < lab[i].size(); j++) {
	if (lab[i][j].second == x) {
	  lab[i][j].first += none;
	  break;
	}
      }
      sort(lab[i].begin(), lab[i].end());
    }
    else {
      for (i = 0; i < add.size(); i++) {
	add[i] += x;
      }
      for (j = 0; j < lab[lab.size() - 1].size(); j++) {
	lab[lab.size() - 1][j].first += x;
      }
    }
    ll left, right;
    if (t == 1) {
      left = pre; right = pre + 2;
    }
    else if (t == 2) {
      left = pre - 1; right = pre + 2;
    }
    else {
      if (x >= 0) {
	left = pre; right = num + 2;
      }
      else {
	left = 0; right = pre + 2;
      }
    }
    while (left + 1 < right) {
      ll mid = (left + right) / 2; 
      int cnt = 0;
      for (i = 0; i < add.size(); i++) {
	int idx = lower_bound(lab[i].begin(), lab[i].end(), pll(mid - add[i], -1)) - lab[i].begin();
	cnt += block - idx;
      }
      int idx = lower_bound(lab[lab.size() - 1].begin(), lab[lab.size() - 1].end(), pll(mid, -1)) - lab[lab.size() - 1].begin();
      cnt += lab[lab.size() - 1].size() - idx;
      if (cnt >= mid) {
	left = mid;
      }
      else {
	right = mid;
      }
    }
    printf("%lld\n", left);
    pre = left;
    /*
    for (i = 0; i < lab.size(); i++) {
      for (j = 0; j < lab[i].size(); j++) {
	printf("(%lld, %lld) ", lab[i][j].first, lab[i][j].second);
      }
      cout << endl;
    }
    */
  }
}
											      
/*
5
1 1
1 2
1 3
1 4
1 5

4
1 1
1 2
1 3
2 2

5
1 1
1 2
1 3
3 2
3 -10

10
1 396579765
1 798135558
1 901129114
3 -929424919
2 3
1 -643609488
3 697031258
3 -245746533
1 -804449362
2 2
*/
