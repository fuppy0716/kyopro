#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i,a,b) for(i=a;i<b;i++)
#define rloop(i,a,b) for(i=a;i>=b;i--)
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

ll x[200005];
ll x_inv[200005];
ll cmb(ll a, ll b) {
	return (x[a] * x_inv[b] % MOD*x_inv[a - b] % MOD) % MOD;
}
ll get_inv(ll x) {
	ll m = MOD - 2;
	ll s = 1;
	while (m != 0) {
		if (m & 1)s = (s*x) % MOD;
		x = (x*x) % MOD;
		m >>= 1;
	}
	return s;
}


int main() {
	ll h, w, a, b, i;
	cin >> h >> w >> a >> b;
	x[0] = x_inv[0] = 1;
	loop(i, 0, w + h + 3) {
		x[i + 1] = x[i] * (i + 1) % MOD;
		x_inv[i + 1] = get_inv(x[i + 1]);
	}
	vl p1(h - a, 0), p2(h, 0);
	p1[0] = 1;
	p2[h - 1] = 1;
	loop(i, 1, h - a) {
		p1[i] = (p1[i - 1] * (i + b - 1) / i) % MOD;
	}
	rloop(i, h - 2, 0) {
		p2[i] = (p2[i + 1] * (h + w - 2 - b - i) / (h - 1 - i)) % MOD;
	};
	ll ans = 0;
	loop(i, 0, h - a) {
		ans = ans + (cmb(i + b - 1, b - 1)*cmb(h - i + w - b - 2, w - b - 1)) % MOD;
		ans %= MOD;
	}
	cout << ans << endl;
}