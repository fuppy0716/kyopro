#include "bits/stdc++.h"
#include <unordered_set>
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

#define N 5010
vll dp(N, vl(N));

ll mod_pow(ll x, ll p, ll M) {
	ll a = 1;
	while (p) {
		if (p % 2)
			a = a*x%M;
		x = x*x%M;
		p /= 2;
	}
	return a;
}

ll mod_inverse(ll a, ll m) {
	return mod_pow(a, m - 2, m);
}


int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	int i, j, k;
	int m = s.size();

	dp[0][0] = 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j <= i; j++) {
			if (j == 0) {
				dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
			}
			else {
				dp[i + 1][j - 1] = (dp[i + 1][j - 1] + dp[i][j]) % MOD;
			}
			dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j] * 2) % MOD;
		}
	}

	ll ans = dp[n][m];
	ans = (ans * mod_inverse(mod_pow(2, m, MOD), MOD)) % MOD;
	while (ans < 0) {
		ans += MOD;
	}
	cout << ans << endl;

}