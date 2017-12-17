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



//rmq �Ɏg�p
const ll MAX_N = 1 << 21;
int n;
vector<pll> dat(2 * MAX_N - 1);
vl a(MAX_N);


//rmq�Ɏg�p
void init(int k, int l, int r) {
	if (r - l == 1) {
		dat[k].first = a[l];
		dat[k].second = l;
	}
	else {
		int lch = 2 * k + 1, rch = 2 * k + 2;
		init(lch, l, (l + r) / 2);
		init(rch, (l + r) / 2, r);
		if (dat[lch].first >= dat[rch].first) {
			dat[k] = dat[lch];
		}
		else {
			dat[k] = dat[rch];
		}

	}
}

//k�Ԗڂ̒l��a�ɕύX
//rmq�Ɏg�p
void update(int k, int a, int v, int l, int r) {
	if (r - l == 1) {
		dat[v].first = a;
	}
	else {
		if (k < (l + r) / 2)
			update(k, a, 2 * v + 1, l, (l + r) / 2);
		else {
			update(k, a, 2 * v + 2, (l + r) / 2, r);
		}
		if (dat[2 * v + 1].first >= dat[2 * v + 2].first) {
			dat[k] = dat[2 * v + 1];
		}
		else {
			dat[k] = dat[2 * v + 2];
		}
	}
}

//rmq�Ɏg�p
//[a,b)�̍ŏ��l�����߂�
//���̂ق��̈����͌v�Z�̊ȒP�̂��߂̈���
//k�͐ړ_�̔ԍ�,l,r�͂��̐ړ_��[l,r)�ɑΉ����Ă��邱�Ƃ�\��
//�]���āA�O�����query(a,b,0,0,n)�Ƃ��Ă��
pll query(int a, int b, int k, int l, int r) {
	if (r <= a || b <= l) {
		return pll(-1, inf);
	}
	if (a <= l && r <= b) {
		return dat[k];
	}
	else {
		pll ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
		pll ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
		if (ul.first >= ur.first) {
			return ul;
		}
		else {
			return ur;
		}
	}
}

int main() {
	int d, k, i, j;
	cin >> n >> d >> k;
	vector<pll> vp;
	for (i = 0; i < n; i++) {
		cin >> a[i];
		vp.push_back(pll(a[i], i));
	}
	sort(vp.begin(), vp.end());
	init(0, 0, n);
	ll ans = -INF;
	ll buyd, selld;
	for (i = 0; i < n; i++) {
		ll buy = a[i];
		pll sell = query(i, min(i + d + 1, n), 0, 0, n);
		if (ans < (sell.first - buy) * k) {
			buyd = i;
			selld = sell.second;
			ans = (sell.first - buy)*k;
		}
	}
	cout << ans << endl;
	if (ans) {
		cout << buyd << " " << selld << endl;
	}
}



int main() {
	int n, d, k, i, j;
	cin >> n >> d >> k;
	vl x(n);
	for (i = 0; i < n; i++) {
		cin >> x[i];
	}
	ll ans = 0;
	ll buyd, selld;
	deque<int> dq;
	for (i = 0; i <= d; i++) {
		while (!dq.empty() && x[dq.back()] < x[i]) {
			dq.pop_back();
		}
		dq.push_back(i);
	}
	for (i = 0; i < n; i++) {
		if (ans < (x[dq[0]] - x[i])*k) {
			ans = (x[dq[0]] - x[i])*k;
			buyd = i;
			selld = dq[0];
		}
		if (i + d + 1 < n) {
			while (!dq.empty() && x[dq.back()] < x[i + d + 1]) {
				dq.pop_back();
			}
			dq.push_back(i + d + 1);
		}
		dq.push_back(i + d + 1);
		while (!dq.empty() && dq.front() <= i) {
			dq.pop_front();
		}
	}
	cout << ans << endl;
	if (ans) {
		cout << buyd << " " << selld << endl;
	}
}