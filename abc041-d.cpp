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
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };



int main() {
	int n, m, i, j, k, l;
	cin >> n >> m;
	vll Gout(n, vl()), Gin(n, vl());
	for (i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		Gout[x].push_back(y);
		Gin[y].push_back(x);
	}
	/*
	DEBUG(n); DEBUG(m);
	cout << endl;
	for (i = 0; i < n; i++) {
	for (j = 0; j < Gin[i].size(); j++) {
	cout << Gin[i][j] << " ";
	}
	cout << endl;
	}
	cout << endl;
	for (i = 0; i < n; i++) {
	for (j = 0; j < Gout[i].size(); j++) {
	cout << Gout[i][j] << " ";
	}
	cout << endl;
	}
	cout << endl;
	*/
	vll dp(n + 1, vl(1 << n));
	dp[0][0] = 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < (1 << n); j++) {
			if (dp[i][j]) {
				for (k = 0; k < n; k++) {
					bool flag = true;
					if ((j & (1 << k))) {
						continue;
					}
					for (l = 0; l < Gin[k].size(); l++) {
						int a = (1 << Gin[k][l]);
						if ((a & j) == 0) {
							flag = false;
							break;
						}
					}
					if (flag) {
						dp[i + 1][(j | (1 << k))] += dp[i][j];
					}
				}
			}
		}
		/*
		for (int i0 = 0; i0 <= n; i0++) {
		for (int j0 = 0; j0 < (1 << n); j0++) {
		cout << dp[i0][j0] << " ";
		}
		cout << endl;
		}
		cout << endl;
		*/
	}
	cout << dp[n][(1 << n) - 1] << endl;

}