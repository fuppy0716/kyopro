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
	int n, i, j;
	ll a, b;
	cin >> n >> a >> b;
	if (a > b) {
		swap(a, b);
	}
	vl s(n + 1);
	s[0] = -INF;
	for (i = 1; i <= n; i++) {
		cin >> s[i];
	}
	for (i = 0; i <= n - 2; i++) {
		if (s[i + 2] - s[i] < a) {
			cout << 0 << endl;
			return 0;
		}
	}
	vl dp(n + 1);
	dp[0] = 1;
	vl sum(n + 2);
	sum[1] = 1;
	int last = 0;
	for (i = 1; i <= n; i++) {
		/*
		for (j = last; j < i; j++) {
		if (s[i] - s[j] < b) {
		break;
		}
		dp[i] += dp[j];
		dp[i] %= MOD;
		}
		*/
		auto itr = upper_bound(s.begin() + last, s.begin() + i, s[i] - b);
		int k = itr - s.begin();
		dp[i] += sum[k] - sum[last] + MOD;
		dp[i] %= MOD;
		sum[i + 1] = (sum[i] + dp[i]) % MOD;
		if (s[i] - s[i - 1] < a) {
			last = i - 1;
		}
	}
	//DEBUG_VEC(dp);
	ll ans = 0;
	for (i = last; i <= n; i++) {
		ans += dp[i];
		ans %= MOD;
	}
	cout << ans << endl;
}