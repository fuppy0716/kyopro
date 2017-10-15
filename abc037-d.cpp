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

#define H 1010
#define W 1010
vii a(H, vi(W));
vll dp(H, vl(W, -1));
int h, w;

ll solve(int i, int j) {
	ll res = 1;
	for (int k = 0; k < 4; k++) {
		int nxi = i + dy[k], nxj = j + dx[k];
		if (nxi >= 0 && nxi < h && nxj >= 0 && nxj < w) {
			if (a[i][j] < a[nxi][nxj]) {
				if (dp[nxi][nxj] != -1) {
					res = (res + dp[nxi][nxj]) % MOD;
				}
				else {
					res = (res + solve(nxi, nxj)) % MOD;
				}
			}
		}
	}
	dp[i][j] = res;
	return res;
}

int main() {
	int  i, j;
	scanf("%d%d", &h, &w);
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (dp[i][j] == -1) {
				solve(i, j);
			}
		}
	}
	ll ans = 0;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			ans = (ans + dp[i][j]) % MOD;
		}
	}
	while (ans < 0) {
		ans += MOD;
	}
	printf("%lld\n", ans);
}