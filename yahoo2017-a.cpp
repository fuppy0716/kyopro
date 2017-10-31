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
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	string s;
	cin >> s;
	int n = s.size(), i, j;
	for (i = 0; i < n; i++) {
		if (s[i] != 'y' && s[i] != 'a' && s[i] != 'h'&&s[i] != 'o') {
			s[i] = '?';
		}
	}
	vii dp(n + 1, vi(15, inf));
	dp[0][0] = dp[0][5] = dp[0][10] = 1;
	dp[0][1] = dp[0][6] = dp[0][11] = 2;
	dp[0][2] = dp[0][7] = dp[0][12] = 3;
	dp[0][3] = dp[0][8] = dp[0][13] = 4;
	dp[0][4] = dp[0][9] = dp[0][14] = 0;
	for (i = 0; i < n; i++) {
		if (s[i] == '?') {
			for (j = 5; j < 10; j++) {
				dp[i + 1][j] = min(dp[i][j] + 1, dp[i + 1][j]);
				dp[i + 1][j] = min(dp[i][j - 1] + 1, dp[i + 1][j]);
				dp[i + 1][j] = min(dp[i][j - 2] + 2, dp[i + 1][j]);
				dp[i + 1][j] = min(dp[i][j - 3] + 3, dp[i + 1][j]);
				dp[i + 1][j] = min(dp[i][j - 4] + 4, dp[i + 1][j]);
			}
			for (j = 0; j < 5; j++) {
				dp[i + 1][j] = dp[i + 1][j + 5];
			}
		}
		if (s[i] == 'y') {
			for (j = 5; j < 10; j++) {
				if (j == 5) {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 1]);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 2] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 3] + 2);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 4] + 3);
				}
				else {
					dp[i + 1][j] = min(dp[i][j] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 1] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 2] + 2, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 3] + 3, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 4] + 4, dp[i + 1][j]);
				}
			}
			for (j = 0; j < 5; j++) {
				dp[i + 1][j] = dp[i + 1][j + 5];
			}
		}
		if (s[i] == 'a') {
			for (j = 5; j < 10; j++) {
				if (j == 6) {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 1]);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 2] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 3] + 2);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 4] + 3);
				}
				else {
					dp[i + 1][j] = min(dp[i][j] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 1] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 2] + 2, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 3] + 3, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 4] + 4, dp[i + 1][j]);
				}
			}
			for (j = 0; j < 5; j++) {
				dp[i + 1][j] = dp[i + 1][j + 5];
			}
		}
		if (s[i] == 'h') {
			for (j = 5; j < 10; j++) {
				if (j == 7) {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 1]);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 2] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 3] + 2);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 4] + 3);
				}
				else {
					dp[i + 1][j] = min(dp[i][j] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 1] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 2] + 2, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 3] + 3, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 4] + 4, dp[i + 1][j]);
				}
			}
			for (j = 0; j < 5; j++) {
				dp[i + 1][j] = dp[i + 1][j + 5];
			}
		}
		if (s[i] == 'o') {
			for (j = 5; j < 10; j++) {
				if (j == 8 || j == 9) {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 1]);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 2] + 1);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 3] + 2);
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 4] + 3);
				}
				else {
					dp[i + 1][j] = min(dp[i][j] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 1] + 1, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 2] + 2, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 3] + 3, dp[i + 1][j]);
					dp[i + 1][j] = min(dp[i][j - 4] + 4, dp[i + 1][j]);
				}
			}
			for (j = 0; j < 5; j++) {
				dp[i + 1][j] = dp[i + 1][j + 5];
			}
		}
	}
	int ans = inf;
	ans = min(dp[n][4], min(dp[n][3] + 1, min(dp[n][2] + 2, min(dp[n][1] + 3, dp[n][0] + 4))));
	cout << ans << endl;
}