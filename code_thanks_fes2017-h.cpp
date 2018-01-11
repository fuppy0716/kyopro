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

#define N 100011
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


//‰ð•ú1:•½•û•ªŠ„
int main() {
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	init(n);
	int b = sqrt(m);
	vi a1(m), a2(m);
	for (i = 0; i < m; i++) {
		scanf("%d%d", &a1[i], &a2[i]);
		a1[i]--; a2[i]--;
	}
	int q;
	cin >> q;
	if (m == 0) {
		for (i = 0; i < q; i++) {
			cout << -1 << endl;
		}
		return 0;
	}
	vi x(q), y(q);
	for (i = 0; i < q; i++) {
		scanf("%d%d", &x[i], &y[i]);
		x[i]--; y[i]--;
	}
	vii judge(m / b + 2, vi(q));
	if (m%b == 0) {
		judge.resize(m / b + 1);
	}
	i = 1;
	while ((i - 1)*b + b < m) {
		for (j = 0; j < b; j++) {
			unite(a1[(i - 1)*b + j], a2[(i - 1)*b + j]);
		}
		for (int k = 0; k < q; k++) {
			if (same(x[k], y[k])) {
				judge[i][k] = 1;
			}
		}
		i++;
	}
	for (j = 0; (i - 1)*b + j < m; j++) {
		unite(a1[(i - 1)*b + j], a2[(i - 1)*b + j]);
	}
	for (int k = 0; k < q; k++) {
		if (same(x[k], y[k])) {
			judge[i][k] = 1;
		}
	}
	vector<pii> time1(q);
	vi time2(q);
	for (i = 0; i < q; i++) {
		if (!judge[judge.size() - 1][i]) {
			time2[i] = -1;
		}
	}
	for (i = 0; i < q; i++) {
		int left = 0, right = judge.size();
		while (left + 1 < right) {
			int mid = (left + right) / 2;
			if (judge[mid][i]) {
				right = mid;
			}
			else {
				left = mid;
			}
		}
		time1[i].first = left;
		time1[i].second = i;
	}
	/*
	cout << "judge" << endl;
	for (i = 0; i < judge.size(); i++) {
	for (j = 0; j < q; j++) {
	cout << judge[i][j] << " ";
	}
	cout << endl;
	}
	*/
	sort(time1.begin(), time1.end());
	/*
	cout << "time1" << endl;
	for (i = 0; i < q; i++) {
	cout << time1[i].first << " " << time1[i].second << endl;
	}
	*/
	init(n);
	int now = 0;
	int k;
	for (i = 0; i * b < m; i++) {
		for (j = 0; j < b && i*b + j < m; j++) {
			unite(a1[i*b + j], a2[i * b + j]);
			for (k = now; k < time1.size(); k++) {
				if (time1[k].first != i) {
					break;
				}
				int idx = time1[k].second;
				if (time2[idx] != 0) {
					continue;
				}
				if (same(x[idx], y[idx])) {
					time2[idx] = i*b + j + 1;
				}
			}
		}
		now = k;
	}
	for (i = 0; i < q; i++) {
		cout << time2[i] << endl;
	}
}