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
#define pll pair<ll,ll>
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



class SegmentTree {
public:
	const ll MAX_N = 1 << 20;
	int n;
	vl dat;
	vl a;

	SegmentTree(int _n, vl _a) :n(_n), a(_a) { dat.resize(2 * MAX_N - 1); }
	SegmentTree() { dat.resize(2 * MAX_N - 1); }

	void init(int k, int l, int r) {
		if (r - l == 1) {
			dat[k] = a[l];
		}
		else {
			int lch = 2 * k + 1, rch = 2 * k + 2;
			init(lch, l, (l + r) / 2);
			init(rch, (l + r) / 2, r);
			dat[k] = min(dat[lch], dat[rch]);
		}
	}


	//k番目の値をaに変更
	void update(int k, ll a, int v, int l, int r) {
		if (r - l == 1) {
			dat[v] = a;
		}
		else {
			if (k < (l + r) / 2)
				update(k, a, 2 * v + 1, l, (l + r) / 2);
			else {
				update(k, a, 2 * v + 2, (l + r) / 2, r);
			}
			dat[v] = min(dat[v * 2 + 1], dat[v * 2 + 2]);
		}
	}

	//[a,b)の最小値を求める
	//後ろのほうの引数は計算の簡単のための引数
	//kは接点の番号,l,rはその接点が[l,r)に対応していることを表す
	//従って、外からはquery(a,b,0,0,n)としてよぶ
	ll query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) {
			return INF;
		}
		if (a <= l && r <= b) {
			return dat[k];
		}
		else {
			ll ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
			ll ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(ul, ur);
		}
	}

};

///////////////
////sum////////
///////////////

// updateパターン
// addパターンはeval,updateのいくつかの=を+=にする, -2*INFを0にする
class LazySegmentTree {
public:
	int n;
	vl node, lazy;

	LazySegmentTree(vl a) {
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1);
		lazy.resize(2 * n - 1, -2*INF);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			node[i] = node[i * 2 + 1] + node[i * 2 + 2];
		}
	}

	// k番目のノードについて遅延評価を行う
	inline void eval(int k, int l, int r) {
		if (lazy[k] != -2 * INF) {
			node[k] = (r - l) * lazy[k];
			if (r - l > 1) {
				lazy[2 * k + 1] = lazy[k]; /////
				lazy[2 * k + 2] = lazy[k]; /////
			}
			lazy[k] = -2 * INF;
		}
	}

	// [a, b)をxにする
	void add(int a, int b, ll x, int k, int l, int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = x;
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = node[2 * k + 1] + node[2 * k + 2];
		}
	}

	ll getsum(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		ll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
		ll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
		return resl + resr;
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




signed main() {
	int _n, x, i, j;
	scanf("%lld%lld", &_n, &x);
	a.resize(2 * _n);
	vi b(_n);
	for (i = 0; i < _n; i++) {
		scanf("%lld", &b[i]);
	}
	n = 2 * _n;
	init(0, 0, n);
	for (i = 0; i < _n; i++) {
		update(i, b[i], 0, 0, n);
		update(i + _n, b[i], 0, 0, n);
	}
	ll ans = INF;
	for (i = 0; i < _n; i++) {
		ll res = 0;
		res += i*x;
		for (j = 0; j < _n; j++) {
			res += query(j, j + i + 1, 0, 0, n);
		}
		ans = min(ans, res);
	}
	for (i = 0; i < _n; i++) {
		ll res = 0;
		res += i*x;
		for (j = _n; j < 2 * _n; j++) {
			res += query(j - i, j + 1, 0, 0, n);
		}
		ans = min(ans, res);
	}
	printf("%lld\n", ans);
}





