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


template <typename T>
class SegmentTree {
public:
  using F = function<T(T&, T&)>;
  int n;
  vector<T > dat;
  F query_func;
  F update_func;
  T e; // �P�ʌ�
  
  SegmentTree(vector<T> a, F query_func, F update_func, T e) :n(a.size()), query_func(query_func), update_func(update_func), e(e) {
    dat.resize(4 * n);
    init(0, 0, n, a);
  }

  void init(int k, int l, int r, vector<T> &a) {
    if (r - l == 1) {
      dat[k] = a[l];
    }
    else {
      int lch = 2 * k + 1, rch = 2 * k + 2;
      init(lch, l, (l + r) / 2, a);
      init(rch, (l + r) / 2, r, a);
      dat[k] = query_func(dat[lch], dat[rch]);
    }
  }

  //k�Ԗڂ̒l��a�ɕύX
  void update(int k, T a, int v, int l, int r) {
    if (r - l == 1) {
      dat[v] = update_func(dat[v], a);
    }
    else {
      if (k < (l + r) / 2)
        update(k, a, 2 * v + 1, l, (l + r) / 2);
      else {
        update(k, a, 2 * v + 2, (l + r) / 2, r);
      }
      dat[v] = query_func(dat[v * 2 + 1], dat[v * 2 + 2]);
    }
  }
    

  //[a,b)�̍ŏ��l�����߂�
  //���̂ق��̈����͌v�Z�̊ȒP�̂��߂̈���
  //k�͐ړ_�̔ԍ�,l,r�͂��̐ړ_��[l,r)�ɑΉ����Ă��邱�Ƃ�\��
  //�]���āA�O�����query(a,b,0,0,n)�Ƃ��Ă��
  T query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
      return e;
    }
    if (a <= l && r <= b) {
      return dat[k];
    }
    else {
      T ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
      T ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return query_func(ul, ur);
    }
  }

  // �����𖞂����ĉE��T��
  int find(int a, int b, int k, int l, int r, int x) {
    // �����𒼂�
    if (dat[k] < x || r <= a || b <= l) return -1;
    if (l + 1 == r) {
      // �����𒼂�
      if (dat[k] >= x) return l;
      else return -1;
    }
    int rv = find(a, b, 2 * k + 2, (l + r) / 2, r, x);
    if (rv != -1) return rv;
    return find(a, b, 2 * k + 1, l, (l + r) / 2, x);
  }
};


template <typename T1, typename T2>
class LazySegmentTree {
public:
  using F = function<T1(T1&, T1&)>; // query_func
  using G = function<T2(T2&, T2&)>; // update_func
  using H = function<T1(T1&, T2&, int, int)>; // lazy to node (node, lazy, left, right)
  int n;
  vector<T1> node;
  vector<T2> lazy;
  F query_func;
  G update_func;
  H eval_func;
  T1 e1;
  T2 e2;

  LazySegmentTree(vector<T1> a, F query_func, G update_func, H eval_func, T1 e1, T2 e2)
    :query_func(query_func), update_func(update_func), eval_func(eval_func), e1(e1), e2(e2)
  {
    int _n = a.size();
    n = 1; while (n < _n) n *= 2;
    node.resize(2 * n - 1, e1);
    lazy.resize(2 * n - 1, e2);
    for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
    for (int i = n - 2; i >= 0; i--) {
      node[i] = query_func(node[i * 2 + 1], node[i * 2 + 2]);
    }
  }

  // k�Ԗڂ̃m�[�h�ɂ��Ēx���]�����s��
  inline void eval(int k, int l, int r) {
    if (lazy[k] != e2) { // Change
      node[k] = eval_func(node[k], lazy[k], l, r);
      if (r - l > 1) {
        lazy[2 * k + 1] = update_func(lazy[2*k + 1], lazy[k]);
        lazy[2 * k + 2] = update_func(lazy[2*k + 2], lazy[k]);
      }
      lazy[k] = e2; // Change
    }
  }

  // [a, b)��x�ɂ���
  void update(int a, int b, T2 x, int k, int l, int r) {
    // k �Ԗڂ̃m�[�h�ɑ΂��Ēx���]�����s��
    eval(k, l, r);
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) {
      lazy[k] = update_func(lazy[k], x);
      eval(k, l, r);
    }
    else {
      update(a, b, x, 2 * k + 1, l, (l + r) / 2);
      update(a, b, x, 2 * k + 2, (l + r) / 2, r);
      node[k] = query_func(node[2 * k + 1], node[2 * k + 2]);
    }
  }

  T1 query(int a, int b, int k, int l, int r) {
    eval(k, l, r);
    if (b <= l || r <= a) return e1;
    if (a <= l && r <= b) return node[k];
    T1 resl = query(a, b, 2 * k + 1, l, (l + r) / 2);
    T1 resr = query(a, b, 2 * k + 2, (l + r) / 2, r);
    return query_func(resl, resr);
  }
};



///////////////
////sum////////
///////////////

// update�p�^�[��
// add�p�^�[����eval,update�̂�������=��+=�ɂ���, -2*INF��0�ɂ���
class LazySegmentTree {
public:
  int n;
  vl node, lazy;

  LazySegmentTree(vl a) {
    int _n = a.size();
    n = 1; while (n < _n) n *= 2;
    node.resize(2 * n - 1);
    lazy.resize(2 * n - 1, -2*INF); // Change
    for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
    for (int i = n - 2; i >= 0; i--) {
      node[i] = node[i * 2 + 1] + node[i * 2 + 2];
    }
  }

  // k�Ԗڂ̃m�[�h�ɂ��Ēx���]�����s��
  inline void eval(int k, int l, int r) {
    if (lazy[k] != -2 * INF) { // Change
      node[k] = (r - l) * lazy[k]; // Change
      if (r - l > 1) {
        lazy[2 * k + 1] = lazy[k]; // Change
        lazy[2 * k + 2] = lazy[k]; //Change
      }
      lazy[k] = -2 * INF; // Change
    }
  }

  // [a, b)��x�ɂ���
  void add(int a, int b, ll x, int k, int l, int r) {
    // k �Ԗڂ̃m�[�h�ɑ΂��Ēx���]�����s��
    eval(k, l, r);
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) {
      lazy[k] = x; // Change
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
//�ő�l///
///////////
class LazySegmentTree {
public:
	int n;
	vl node, lazy;
	bool ismax; //true�Ȃ�ő�l�Afalse�Ȃ�ŏ��l

	LazySegmentTree(vl a, bool _ismax) {
		ismax = _ismax;
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1);
        fill(all(node), INF * (1 - (int)ismax * 2));
		lazy.resize(2 * n - 1, 0);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			if (ismax) node[i] = max(node[i * 2 + 1], node[i * 2 + 2]);
			else node[i] = min(node[i * 2 + 1], node[i * 2 + 2]);
		}
	}

	// k�Ԗڂ̃m�[�h�ɂ��Ēx���]�����s��
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
		// k �Ԗڂ̃m�[�h�ɑ΂��Ēx���]�����s��
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
		if (b <= l || r <= a) return (ismax ? -INF : INF);
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





