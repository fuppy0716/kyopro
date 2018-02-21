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
#define fi first
#define se second
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define all(c) c.begin(),c.end()
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

typedef complex<double> P;

vector<P> fft(vector<P> v, bool rev = false) {
	int n = v.size(), i, j, m;

	for (i = 0, j = 1; j<n - 1; j++) {
		for (int k = n >> 1; k>(i ^= k); k >>= 1);
		if (i>j) swap(v[i], v[j]);
	}
	for (int m = 2; m <= n; m *= 2) {
		double deg = (rev ? -1 : 1) * 2 * acos(-1) / m;
		P wr(cos(deg), sin(deg));
		for (i = 0; i<n; i += m) {
			P w(1, 0);
			for (int j1 = i, j2 = i + m / 2; j2<i + m; j1++, j2++) {
				P t1 = v[j1], t2 = w*v[j2];
				v[j1] = t1 + t2, v[j2] = t1 - t2;
				w *= wr;
			}
		}
	}
	if (rev) rep(i, n) v[i] *= 1.0 / n;
	return v;
}

vector<P> MultPoly(vector<P> a, vector<P> b) {
	a = fft(a), b = fft(b);
	for (int i = 0; i<a.size(); i++) a[i] *= b[i];
	return fft(a, true);
}
int main() {
	int n;
	cin >> n;
	vector<P> a(2 * n + 10), b(2 * n + 10);
	ll x = n;
	while (x&(x - 1)) x++;
	x *= 4;
	a.resize(x);
	b.resize(x);
	rep1(i, n) {
		int c, d;
		cin >> c >> d;
		a[i].real(c); b[i].real(d);
	}
	auto ans = MultPoly(a, b);
	rep1(i, 2 * n) {
		cout << (ll)(ans[i].real() + 0.5) << endl;
	}
}