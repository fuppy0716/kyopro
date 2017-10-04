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
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define N 100010
#define M 200010
vi par(N); //e
vi ran(N); //–Ø‚Ì[‚³

		   //n—v‘f‚Å‰Šú‰»
void init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		par[i] = i;
		ran[i] = 0;
	}
}

//–Ø‚Ìª‚ð‹‚ß‚é
int find(int x) {
	if (par[x] == x) {
		return x;
	}
	else {
		return par[x] = find(par[x]);
	}
}

//x‚Æy‚Ì‘®‚·‚éW‡‚ð•¹‡
void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) {
		return;
	}
	if (ran[x]<ran[y]) {
		par[x] = y;
	}
	else {
		par[y] = x;
		if (ran[x] == ran[y]) {
			ran[x]++;
		}
	}
}

//x‚Æy‚ª“¯‚¶W‡‚É‘®‚·‚é‚©”Û‚©
bool same(int x, int y) {
	return find(x) == find(y);
}


/*
cin.tie(0);
ios::sync_with_stdio(false);
*/
int main() {
	int n, m, i, j;
	cin >> n >> m;
	vl v(n);
	for (i = 0; i < n; i++) {
		cin >> v[i];
	}
	init(n);
	vi x(m), y(m);
	for (i = 0; i < m; i++) {
		cin >> x[i] >> y[i];
		x[i]--; y[i]--;
		unite(x[i], y[i]);
	}
	vi edge(n);
	for (i = 0; i < m; i++) {
		edge[find(x[i])]++;
	}
	vll num(n, vl());
	for (i = 0; i < n; i++) {
		num[find(i)].push_back(v[i]);
	}
	ll ans = 0;
	for (i = 0; i < n; i++) {
		if (edge[i] == 0) {
			continue;
		}
		if (edge[i] == num[i].size() - 1) {
			ll mn = INF;
			for (j = 0; j < num[i].size(); j++) {
				ans += num[i][j];
				mn = min(mn, num[i][j]);
			}
			ans -= mn;
		}
		else {
			for (j = 0; j < num[i].size(); j++) {
				ans += num[i][j];
			}
		}
	}
	cout << ans << endl;
}