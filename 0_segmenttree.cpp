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

//rmq �Ɏg�p
#define int ll
const ll MAX_N = 1 << 13;
int n;
vl dat(2 * MAX_N - 1);
vi a(MAX_N);


//rmq�Ɏg�p
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

//k�Ԗڂ̒l��a�ɕύX
//rmq�Ɏg�p
void update(int k, int a, int v, int l, int r) {
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

//rmq�Ɏg�p
//[a,b)�̍ŏ��l�����߂�
//���̂ق��̈����͌v�Z�̊ȒP�̂��߂̈���
//k�͐ړ_�̔ԍ�,l,r�͂��̐ړ_��[l,r)�ɑΉ����Ă��邱�Ƃ�\��
//�]���āA�O�����query(a,b,0,0,n)�Ƃ��Ă��
int query(int a, int b, int k, int l, int r) {
	if (r <= a || b <= l) {
		return inf;
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