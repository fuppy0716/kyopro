
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
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	int n, i, j;
	cin >> n;
	vi x(n);
	for (i = 0; i < n; i++) {
		cin >> x[i];
	}
	vii a(n,vi());
	for (i = 1; i < n; i++) {
		int temp;
		cin >> temp;
		temp--;
		a[temp].push_back(i);
	}
	vi mask(n), childx(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < a[i].size(); j++) {
			mask[i] += (1 << a[i][j]);
			childx[i] += x[a[i][j]];
		}
	}
	vector<vector<pii> > dp(n + 1, vector<pii>((1 << n), pii(-1,inf)));
	dp[0][0] = pii(0, 0);
	for (i = 0; i < n; i++) {
		for (j = 0; j < (1 << n); j++) {
			if (dp[i][j].first != -1) {
				for (int k = 0; k < n; k++) {
					if ((j & mask[k]) == mask[k] && (j & (1 << k)) == 0) {
						int sec = dp[i][j].first + x[k];
						int fir = sec - childx[k];
						int nextj = (j & ~mask[k]) | (1 << k);
						dp[i + 1][nextj].first = fir;
						dp[i + 1][nextj].second = min(dp[i + 1][nextj].second, max(sec, dp[i][j].second));
					}
				}
			}
		}
	}
	int ans = inf;
	for (i = 0; i < (1 << n); i++) {
		if (i % 2 == 0) {
			continue;
		}
		ans = min(ans, dp[n][i].second);
	}
	cout << ans << endl;
}

