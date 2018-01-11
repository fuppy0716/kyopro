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
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


int main() {
	ll n, v, i, j;
	cin >> n >> v;
	vl c(n), sum(n);
	ll nokori = v, cost = 0;
	for (i = 0; i < n; i++) {
		cin >> c[i];
		cost += c[i];
		sum[i] = cost;
	}
	nokori -= n;
	if (nokori <= 0) {
		cout << cost << endl;
		return 0;
	}
	vl dp(20000, INF);
	dp[0] = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 20000 - (i + 1); j++) {
			dp[j + (i + 1)] = min(dp[j + (i + 1)], dp[j] + sum[i]);
		}
	}
	if (nokori < 15000) {
		cost += dp[nokori];
		cout << cost << endl;
		return 0;
	}

	int opt = 0;
	for (i = 1; i < n; i++) {
		if (sum[opt] * (i + 1) > sum[i] * (opt + 1)) opt = i;
	}
	ll k = (nokori - 15000) / (opt + 1);
	cost += k*sum[opt] + dp[nokori - (opt + 1)*k];
	cout << cost << endl;
}

