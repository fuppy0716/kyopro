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

///////////////
////sum////////
///////////////

// updateパターン
// addパターンはeval,updateのいくつかの=を+=にする
// また、-2*INF を 0 にする
class LazySegmentTree {
public:
	int n;
	vl node, lazy;

	LazySegmentTree(vl a) {
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1);
		lazy.resize(2 * n - 1, -2 * INF);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			node[i] = (node[i * 2 + 1] + node[i * 2 + 2]) % MOD;
		}
	}

	// k番目のノードについて遅延評価を行う
	inline void eval(int k, int l, int r) {
		if (lazy[k] != -2 * INF) {
			node[k] = (r - l) * lazy[k] % MOD;
			if (r - l > 1) {
				lazy[2 * k + 1] = lazy[k]; /////
				lazy[2 * k + 2] = lazy[k]; /////
			}
			lazy[k] = -2 * INF;
		}
	}

	// [a, b)をxにする
	void update(int a, int b, ll x, int k, int l, int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = x;
			eval(k, l, r);
		}
		else {
			update(a, b, x, 2 * k + 1, l, (l + r) / 2);
			update(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = (node[2 * k + 1] + node[2 * k + 2]) % MOD;
		}
	}

	ll getsum(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		ll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
		ll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
		return (resl + resr) % MOD;
	}
};


///////////
//最大値///
///////////
class LazySegmentTree {
public:
	int n;
	vl node, lazy;
	bool ismax; //trueなら最大値、falseなら最小値

	LazySegmentTree(vl a, bool _ismax) {
		ismax = _ismax;
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1, INF * (1 - (int)ismax * 2));
		lazy.resize(2 * n - 1, 0);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			if (ismax) node[i] = max(node[i * 2 + 1], node[i * 2 + 2]);
			else node[i] = min(node[i * 2 + 1], node[i * 2 + 2]);
		}
	}

	// k番目のノードについて遅延評価を行う
	inline void eval(int k, int l, int r) {
		if (lazy[k] != 0) {
			node[k] += lazy[k];
			if (r - l > 1) {
				lazy[2 * k + 1] += lazy[k]; /////
				lazy[2 * k + 2] += lazy[k]; /////
			}
			lazy[k] = 0;
		}
	}

	void add(int a, int b, ll x, int k, int l, int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] += x; //////
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			if (ismax) node[k] = max(node[2 * k + 1], node[2 * k + 2]);
			else node[k] = min(node[2 * k + 1], node[2 * k + 2]);
		}
	}

	ll getmax(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		ll resl = getmax(a, b, 2 * k + 1, l, (l + r) / 2);
		ll resr = getmax(a, b, 2 * k + 2, (l + r) / 2, r);
		if (ismax) return max(resl, resr);
		else return min(resl, resr);
	}

};





int main() {
	int q, i, j;
	cin >> n >> q;
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	init(0, 0, n);
	for (int unko = 0; unko < q; unko++) {
		char type;
		cin >> type;
		if (type == 'Q') {
			int a, b;
			cin >> a >> b;
			a--; b--;
			cout << getsum(a, b + 1, 0, 0, n) << endl;
		}
		else {
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			add(a, b + 1, c, 0, 0, n);
		}
	}
}