#include "bits/stdc++.h"
#include <unordered_set>
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

#define N 200010
#define K 100010
vi T(K), X(K), Y(K);
vi par1(N); //親
vi ran1(N); //木の深さ
vi par2(N);
vi ran2(N);

//n要素で初期化
void init1(int n) {
	int i;
	for (i = 0; i < n; i++) {
		par1[i] = i;
		ran1[i] = 0;
	}
}

//木の根を求める
int find1(int x) {
	if (par1[x] == x) {
		return x;
	}
	else {
		return par1[x] = find1(par1[x]);
	}
}

//xとyの属する集合を併合
void unite1(int x, int y) {
	x = find1(x);
	y = find1(y);
	if (x == y) {
		return;
	}
	if (ran1[x]<ran1[y]) {
		par1[x] = y;
	}
	else {
		par1[y] = x;
		if (ran1[x] == ran1[y]) {
			ran1[x]++;
		}
	}
}

//xとyが同じ集合に属するか否か
bool same1(int x, int y) {
	return find1(x) == find1(y);
}

void init2(int n) {
	int i;
	for (i = 0; i < n; i++) {
		par2[i] = i;
		ran2[i] = 0;
	}
}

//木の根を求める
int find2(int x) {
	if (par2[x] == x) {
		return x;
	}
	else {
		return par2[x] = find2(par2[x]);
	}
}

//xとyの属する集合を併合
void unite2(int x, int y) {
	x = find2(x);
	y = find2(y);
	if (x == y) {
		return;
	}
	if (ran2[x]<ran2[y]) {
		par2[x] = y;
	}
	else {
		par2[y] = x;
		if (ran2[x] == ran2[y]) {
			ran2[x]++;
		}
	}
}

//xとyが同じ集合に属するか否か
bool same2(int x, int y) {
	return find2(x) == find2(y);
}

int main() {
	int n, k, l, i, j;
	cin >> n >> k >> l;
	init1(n);
	init2(n);
	int p, q;
	for (i = 0; i < k; i++) {
		cin >> p >> q;
		unite1(p - 1, q - 1);
	}
	for (i = 0; i < l; i++) {
		cin >> p >> q;
		unite2(p - 1, q - 1);
	}
	vector<pii> v(n);
	map<pii, int> mp;
	for (i = 0; i < n; i++) {
		v[i] = make_pair(find1(i), find2(i));
		mp[v[i]]++;
	}

	for (i = 0; i < n; i++) {
		cout << mp[v[i]] << " ";
	}
	return 0;
}