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
#define N 200010
const int DAT_SIZE = (1 << 18) - 1;
int n, q;
vl a(N);
vl node(DAT_SIZE), lazy(DAT_SIZE, 0);

void init(int k, int l, int r) {

	int _n = 1; while (_n < n) _n *= 2;
	node.resize(2 * _n - 1);
	lazy.resize(2 * _n - 1, 0);
	for (int i = 0; i < n; i++) node[i + _n - 1] = a[i];
	for (int i = _n - 2; i >= 0; i--) node[i] = node[i * 2 + 1] + node[i * 2 + 2];
	n = _n;
}

// k番目のノードについて遅延評価を行う
inline void eval(int k, int l, int r) {
	// 遅延配列が空でない場合、自ノード及び子ノードへの
	// 値の伝播が起こる
	if (lazy[k] != 0) {
		node[k] += (r - l) * lazy[k]; /////

		// 最下段かどうかのチェックをしよう
		// 子ノードは親ノードの 1/2 の範囲であるため、
		 // 伝播させるときは半分にする
		if (r - l > 1) {
			lazy[2 * k + 1] += lazy[k]; /////
			lazy[2 * k + 2] += lazy[k]; /////
		}

		// 伝播が終わったので、自ノードの遅延配列を空にする
		lazy[k] = 0;
	}
}

void add(int a, int b, ll x, int k, int l, int r) {

	// k 番目のノードに対して遅延評価を行う
	eval(k, l, r);

	// 範囲外なら何もしない
	if (b <= l || r <= a) return;

	// 完全に被覆しているならば、遅延配列に値を入れた後に評価
	if (a <= l && r <= b) {
		lazy[k] += x; //////
		eval(k, l, r);
	}

	// そうでないならば、子ノードの値を再帰的に計算して、
	// 計算済みの値をもらってくる
	else {
		add(a, b, x, 2 * k + 1, l, (l + r) / 2);
		add(a, b, x, 2 * k + 2, (l + r) / 2, r);
		node[k] = node[2 * k + 1] + node[2 * k + 2];
	}
}

ll getsum(int a, int b, int k, int l, int r) {

	// 関数が呼び出されたらまず評価！
	eval(k, l, r);

	if (b <= l || r <= a) return 0;
	if (a <= l && r <= b) return node[k];
	ll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
	ll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
	return resl + resr;
}



///////////
//最大値///
///////////


#define N 200010
const int DAT_SIZE = (1 << 18) - 1;
int n, q;
vl a(N);
vl node(DAT_SIZE), lazy(DAT_SIZE, 0);


void init(int k, int l, int r) {

	int _n = 1; while (_n < n) _n *= 2;
	node.resize(2 * _n - 1);
	lazy.resize(2 * _n - 1, 0);
	for (int i = 0; i < n; i++) node[i + _n - 1] = a[i];
	for (int i = _n - 2; i >= 0; i--) node[i] = max(node[i * 2 + 1], node[i * 2 + 2]);
	n = _n;
}


// k番目のノードについて遅延評価を行う
inline void eval(int k, int l, int r) {
	// 遅延配列が空でない場合、自ノード及び子ノードへの
	// 値の伝播が起こる
	if (lazy[k] != 0) {
		node[k] += lazy[k]; /////

									  // 最下段かどうかのチェックをしよう
									  // 子ノードは親ノードの 1/2 の範囲であるため、
									  // 伝播させるときは半分にする
		if (r - l > 1) {
			lazy[2 * k + 1] += lazy[k]; /////
			lazy[2 * k + 2] += lazy[k]; /////
		}

		// 伝播が終わったので、自ノードの遅延配列を空にする
		lazy[k] = 0;
	}
}

void add(int a, int b, ll x, int k, int l, int r) {

	// k 番目のノードに対して遅延評価を行う
	eval(k, l, r);

	// 範囲外なら何もしない
	if (b <= l || r <= a) return;

	// 完全に被覆しているならば、遅延配列に値を入れた後に評価
	if (a <= l && r <= b) {
		lazy[k] += x; //////
		eval(k, l, r);
	}

	// そうでないならば、子ノードの値を再帰的に計算して、
	// 計算済みの値をもらってくる
	else {
		add(a, b, x, 2 * k + 1, l, (l + r) / 2);
		add(a, b, x, 2 * k + 2, (l + r) / 2, r);
		node[k] = max(node[2 * k + 1], node[2 * k + 2]);
	}
}

ll getsum(int a, int b, int k, int l, int r) {

	// 関数が呼び出されたらまず評価！
	eval(k, l, r);

	if (b <= l || r <= a) return 0;
	if (a <= l && r <= b) return node[k];
	ll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
	ll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
	return max(resl, resr);
}





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