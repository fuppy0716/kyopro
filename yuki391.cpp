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

ll MAXM = 100100;
vl fact(MAXM);
vl C(MAXM);

ll mod_pow(ll x, ll p, ll M) {
	ll a = 1;
	while (p) {
		if (p % 2)
			a = a*x%MOD;
		x = x*x%MOD;
		p /= 2;
	}
	return a;
}

ll mod_inverse(ll a, ll m) {
	return mod_pow(a, m - 2, m);
}

ll nCr(ll n, ll r) {
	ll ret = fact[n];
	ret = (ret*mod_inverse(fact[r], MOD)) % MOD;
	ret = (ret*mod_inverse(fact[n - r], MOD)) % MOD;
	return ret;
}


int main() {
	ll n, m, i, j;
	cin >> n >> m;
	if (n < m) {
		cout << 0 << endl;
		return 0;
	}
	fact[0] = 1;
	for (i = 1; i <= m; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	for (i = 0; i <= m; i++) {
		if (i == 0)
			C[i] = 1;
		else
			C[i] = nCr(m, i);
	}
	ll ans = 0;
	int fugou = 1;
	for (i = 0; i < m; i++) {
		ans = (ans + fugou * ((C[i] * mod_pow(m - i, n, MOD)) % MOD)) % MOD;
		fugou *= (-1);
	}
	while (ans < 0) {
		ans += MOD;
	}
	cout << ans << endl;
}