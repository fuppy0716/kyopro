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
#define N 10001
vi par(N); //e
vi ran(N); //–Ø‚Ì[‚³
vi num(N);

//n—v‘f‚Å‰Šú‰»
void init(int n) {
	int i;
	for (i = 0; i < n; i++)
	{
		par[i] = i;
		ran[i] = 0;
		num[i] = 1;
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
	if (num[x] != num[y]) {
		if (num[x] > num[y]) {
			num[x] += num[y];
			par[y] = x;
		}
		else {
			num[y] += num[x];
			par[x] = y;
		}
	}
	else {
		if (par[y] > par[x]) {
			num[x] += num[y];
			par[y] = x;
		}
		else {
			num[y] += num[x];
			par[x] = y;
		}
	}
}

//x‚Æy‚ª“¯‚¶W‡‚É‘®‚·‚é‚©”Û‚©
bool same(int x, int y) {
	return find(x) == find(y);
}

int main() {
	int n, m, i;
	cin >> n >> m;
	int a, b;
	init(n + 1);
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		unite(a, b);
	}
	for (i = 1; i < n + 1; i++) {
		cout << find(i) << endl;
	}
	return 0;
}