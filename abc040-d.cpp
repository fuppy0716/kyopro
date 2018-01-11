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

#define N 100010
vi par(N); //e
vi ran(N); //–Ø‚Ì[‚³
vi num(N); //—v‘f”

		   //n—v‘f‚Å‰Šú‰»
void init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		num[i] = 1;
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
	int num_x = num[x];
	int num_y = num[y];
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
	x = find(x);
	y = find(y);
	num[x] = num[y] = num_x + num_y;
}

//x‚Æy‚ª“¯‚¶W‡‚É‘®‚·‚é‚©”Û‚©
bool same(int x, int y) {
	return find(x) == find(y);
}

int main() {
	int n, m, i, j;
	cin >> n >> m;
	vector< pair<int, pii> > y(m);
	for (i = 0; i < m; i++) {
		int a, b, y2;
		cin >> a >> b >> y2;
		y[i].first = y2;
		y[i].second.first = --a;
		y[i].second.second = --b;
	}
	sort(y.begin(), y.end());
	reverse(y.begin(), y.end());
	int q;
	cin >> q;
	vector< pair<int, pii> > p(q);
	for (i = 0; i < q; i++) {
		int v, w;
		cin >> v >> w;
		p[i].first = w;
		p[i].second.first = i;
		p[i].second.second = --v;
	}
	sort(p.begin(), p.end());
	reverse(p.begin(), p.end());

	vi ans(q);
	init(n);
	int iy = 0, ip = 0;
	for (int year = 200001; year > 0; year--) {
		while (true) {
			if (iy == m) {
				break;
			}
			if (y[iy].first == year) {
				unite(y[iy].second.first, y[iy].second.second);
				iy++;
			}
			else {
				break;
			}
		}
		while (true) {
			if (ip == q) {
				break;
			}
			if (p[ip].first + 1 == year) {
				ans[p[ip].second.first] = num[find(p[ip].second.second)];
				ip++;
			}
			else {
				break;
			}
		}
		//cout << year << endl;;
	}
	for (i = 0; i < q; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}