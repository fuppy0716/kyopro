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

#define N 300010
const int DAT_SIZE = (1 << 18) - 1;
vl dat(DAT_SIZE), datb(DAT_SIZE);

void add(int a, int b, ll x, int v, int l, int r) {
	if (a <= l && r <= b) {
		dat[v] += x;
	}
	else if (l < b && a < r) {
		datb[v] += (min(b, r) - max(a, l))*x;
		add(a, b, x, v * 2 + 1, l, (l + r) / 2);
		add(a, b, x, v * 2 + 2, (l + r) / 2, r);
	}
}

ll sum(int a, int b, int v, int l, int r) {
	if (r <= a || b <= l) {
		return 0;
	}
	else if (a <= l && r <= b) {
		return dat[v] * (r - l) + datb[v];
	}
	else {
		ll res = (min(b, r) - max(a, l)) * dat[v];
		res += sum(a, b, v * 2 + 1, l, (l + r) / 2);
		res += sum(a, b, v * 2 + 2, (l + r) / 2, r);
		return res;
	}
}


int main() {
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	vi l(n), r(n);
	vii d(m + 3, vi());
	for (i = 0; i < n; i++) {
		scanf("%d%d", &l[i], &r[i]);
		d[r[i] - l[i] + 2].push_back(i);
	}
	int safe = n;
	for (int k = 1; k <= m; k++) {
		int res = 0;
		safe -= d[k].size();
		res += safe;
		for (i = 0; i < d[k].size(); i++) {
			add(l[d[k][i]], r[d[k][i]] + 1, 1, 0, 0, m + 1);
		}
		for (i = 1; k*i <= m; i++) {
			res = res + sum(k*i, k*i + 1, 0, 0, m + 1);
		}
		printf("%d\n", res);

	}
}