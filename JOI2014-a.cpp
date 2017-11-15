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
	int n, m, i, j;
	scanf("%lld%lld", &n, &m);
	vl p(m);
	for (i = 0; i < m; i++) {
		scanf("%lld", &p[i]);
		p[i]--;
	}
	vl a(n - 1), b(n - 1), c(n - 1);
	for (i = 0; i < n - 1; i++) {
		scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	}
	vl count(n);
	for (i = 0; i < m - 1; i++) {
		int p1 = min(p[i], p[i + 1]);
		int p2 = max(p[i], p[i + 1]);
		count[p1]++;
		count[p2]--;
	}
	vl sum(n);
	for (i = 0; i < n - 1; i++) {
		sum[i + 1] = sum[i] + count[i];
	}
	ll ans = 0;
	for (i = 0; i < n - 1; i++) {
		j = sum[i + 1];
		ll cost = min(j*a[i], c[i] + j*b[i]);
		ans += cost;
	}
	printf("%lld\n", ans);
	return 0;
}