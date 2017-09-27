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
	int n, ma, mb, i, j, k;
	cin >> n >> ma >> mb;
	vi a(n), b(n), c(n);
	for (i = 0; i < n; i++) {
		cin >> a[i] >> b[i] >> c[i];
	}
	vii dp(401, vi(401, inf));
	dp[0][0] = 0;
	for (i = 0; i < n; i++) {
		for (j = 400 - a[i]; j >= 0; j--) {
			for (k = 400 - b[i]; k >= 0; k--) {
				if (dp[j][k] != inf) {
					dp[j + a[i]][k + b[i]] = min(dp[j + a[i]][k + b[i]], dp[j][k] + c[i]);
				}
			}
		}
	}
	int ans = inf;
	for (i = 1; i <= 400; i++) {
		if ((i*mb) % ma != 0) {
			continue;
		}
		else if (i*mb / ma > 400) {
			break;
		}
		else {
			ans = min(ans, dp[i][i*mb / ma]);
		}
	}
	if (ans == inf) {
		cout << -1 << endl;
		return 0;
	}
	else {
		cout << ans << endl;
		return 0;
	}
}