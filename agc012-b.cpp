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

#define N 100010
vii G(N, vi());

int main() {
	int n, m, i, j;
	cin >> n >> m;
	vi a(m), b(m);
	for (i = 0; i < m; i++) {
		cin >> a[i] >> b[i];
		a[i]--; b[i]--;
		G[a[i]].push_back(b[i]);
		G[b[i]].push_back(a[i]);
	}
	int q;
	cin >> q;
	vi v(q), d(q), c(q);
	vii dp(11, vi(n, -1));
	for (i = 0; i < q; i++) {
		cin >> v[i] >> d[i] >> c[i];
		v[i]--;
		dp[d[i]][v[i]] = i;
	}
	for (i = 10; i > 0; i--) {
		for (j = 0; j < n; j++) {
			if (dp[i][j] >= 0) {
				for (int k = 0; k < G[j].size(); k++) {
					if (dp[i - 1][G[j][k]] < dp[i][j]) {
						dp[i - 1][G[j][k]] = dp[i][j];
					}
				}
				if (dp[i - 1][j] < dp[i][j]) {
					dp[i - 1][j] = dp[i][j];
				}
			}
		}
	}
	for (i = 0; i < n; i++) {
		if (dp[0][i] == -1) {
			cout << 0 << endl;
		}
		else {
			cout << c[dp[0][i]] << endl;
		}
	}
}