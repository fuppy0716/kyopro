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
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	int n, x, i, j;
	cin >> n >> x;
	vi t(n);
	for (i = 0; i < n; i++) {
		cin >> t[i];
	}
	vi next(n);
	for (i = 0; i < n; i++) {
		next[i] = lower_bound(t.begin(), t.end(), t[i] + x) - t.begin();
		if (next[i] < i + 2) {
			next[i] = i + 2;
			if (next[i] > n) {
				next[i] = n;
			}
		}
	}
	vii dp(n + 1, vi(n + 1));
	dp[0][1] = x;
	for (i = 0; i < n; i++) {
		for (j = 1; j < n; j++) {
			if (dp[i][j]) {
				if (next[i] != n) {
					dp[next[i]][j + 1] = max(dp[next[i]][j + 1], dp[i][j] + min(x, t[next[i]] - t[i]));
				}
				dp[next[i] - 1][j + 1] = max(dp[next[i] - 1][j + 1], dp[i][j] + min(x, t[next[i] - 1] - t[i]));
			}
		}
	}
	for (i = 1; i <= n; i++) {
		int ans = 0;
		for (j = 0; j <= n; j++) {
			ans = max(ans, dp[j][i]);
		}
		cout << ans << endl;
	}
}