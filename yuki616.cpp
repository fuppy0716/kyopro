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


struct Modint {
	ll n;
	static const ll Mod = 1000000007;
	Modint(int n = 0) : n(n) {}
};

Modint operator+(Modint a, Modint b) { return Modint((a.n += b.n) >= mod ? a.n - a.Mod : a.n); }
Modint operator-(Modint a, Modint b) { return Modint((a.n -= b.n) < 0 ? a.n + a.Mod : a.n); }
Modint operator*(Modint a, Modint b) { return Modint(1LL * a.n * b.n % a.Mod); }
Modint &operator+=(Modint &a, Modint b) { return a = a + b; }
Modint &operator-=(Modint &a, Modint b) { return a = a - b; }
Modint &operator*=(Modint &a, Modint b) { return a = a * b; }


int main() {
	int n, k, i, j;
	cin >> n >> k;
	for (i = 0; i < n; i++) {
		cin >> j;
	}
	vector<vector<Modint> > dp(n + 1, vector<Modint>(n*(n - 1) / 2 + 1));
	vector<vector<Modint> > sum(n + 1, vector<Modint>(n*(n - 1) / 2 + 2));
	Modint one(1);
	Modint zero(0);
	dp[0][0] = one;
	sum[0][0] = zero;
	sum[0][1] = one;
	for (i = 0; i < n; i++) {
		for (j = 0; j <= (i + 1)*i / 2; j++) {
			dp[i + 1][j] = sum[i][min(j + 1, i*(i - 1) / 2 + 1)] - sum[i][max(j - i, 0)];
		}
		sum[i][0] = zero;
		for (j = 0; j <= (i + 1)*i / 2; j++) {
			sum[i + 1][j + 1] = sum[i + 1][j] + dp[i + 1][j];
		}
	}
	/*
	for (i = 0; i <= n; i++) {
	for (j = 0; j <= (i - 1)*i / 2; j++) {
	cout << dp[i][j].n << " ";
	}
	cout << endl;
	}

	for (i = 0; i <= n; i++) {
	for (j = 0; j <= (i - 1)*i / 2 + 1; j++) {
	cout << sum[i][j].n << " ";
	}
	cout << endl;
	}
	*/
	cout << sum[n][k + 1].n << endl;
}