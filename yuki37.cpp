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

int main() {
	int t;
	cin >> t;
	int n, i, j;
	cin >> n;
	vi c(n), v(n);
	for (i = 0; i < n; i++) {
		cin >> c[i];
	}
	for (i = 0; i < n; i++) {
		cin >> v[i];
	}
	vll dp(n + 1, vl(t + 1, -1));
	dp[0][0] = 0;
	for (i = 0; i < n; i++) {
		for (j = t; j >= 0; j--) {
			if (dp[i][j] != -1) {
				dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
				for (int k = v[i], cnt = 1; k > 0; k /= 2, cnt++) {
					if (j + c[i] * cnt <= t) {
						dp[i + 1][j + c[i] * cnt] = max(dp[i + 1][j + c[i] * cnt], dp[i + 1][j + c[i] * (cnt - 1)] + k);
					}
					else {
						break;
					}
				}
			}
		}
	}
	ll ans = 0;
	//DEBUG_VEC(dp[0]); DEBUG_VEC(dp[1]); DEBUG_VEC(dp[2]); DEBUG_VEC(dp[3]); DEBUG_VEC(dp[4]); DEBUG_VEC(dp[5]);
	for (i = 0; i <= t; i++) {
		ans = max(ans, dp[n][i]);
	}
	cout << ans << endl;
}