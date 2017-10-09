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
#define pll pair<ll,ll>
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
	ll n, m, i, j, k, l;
	scanf("%lld\n%lld", &n, &m);
	vll a(m, vl(m));
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			scanf("%lld", &a[i][j]);
		}
	}
	vector<vll> dp(36, vll(m, vl(m)));
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			dp[0][i][j] = a[i][j];
		}
	}
	for (i = 1; i <= 35; i++) {
		for (j = 0; j < m; j++) {
			for (k = 0; k < m; k++) {
				for (l = 0; l < m; l++) {
					dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][l] + dp[i - 1][l][k]);
				}
			}
		}
	}
	n--;
	ll sum = 0;
	vector<vll> res(36, vll(m, vl(m)));
	for (i = 0; i <= 35; i++) {
		if (n&(1LL << i)) {
			for (j = 0; j < m; j++) {
				for (k = 0; k < m; k++) {
					for (l = 0; l < m; l++) {
						if (i) {
							res[i][j][k] = max(res[i][j][k], res[i - 1][j][l] + dp[i][l][k]);
						}
						else {
							res[0][j][k] = dp[0][j][k];
						}
						sum = max(sum, res[i][j][k]);
					}
				}
			}
		}
		else {
			for (j = 0; j < m; j++) {
				for (k = 0; k < m; k++) {
					if (i) {
						res[i][j][k] = res[i - 1][j][k];
					}
					else {
						res[i][j][k] = 0;
					}
				}
			}
		}
	}
	printf("%lld\n", sum);
}