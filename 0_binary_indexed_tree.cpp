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


class Bit {
public:
	int n;
	vl bit; // 1-index

	Bit(int _n) { n = _n; bit.resize(n + 1); }


	// [1, i]の和
	ll sum(int i) {
		ll s = 0;
		while (i > 0) {
			s += bit[i];
			i -= i & -i;
		}
		return s;
	}

	//iは1-index
	void add(int i, ll x) {
		while (i <= n) {
			bit[i] += x;
			i += i & -i;
		}
	}

	// 1,2,...,nを並び替えた順列をバブルソートで
	// 順番通りにするための交換回数
	ll bubble(vi p) {
		int n = p.size();
		ll ans = 0;
		for (int j = 0; j < n; j++) {
			ans += (j - sum(p[j]));
			add(p[j], 1);
		}
		return ans;
	}

	// bitに入ってる中でx番目に小さい数を求める
	// 1番小さい数はx = 1;
	// bitに3を入れる→add(3, 1), 3を出す→add(3, -1)
	ll min_xth(int x) {
		int left = 0, right = 200000;
		while (left + 1 < right) {
			int mid = (left + right) / 2;
			int temp = sum(mid);
			if (temp < x) {
				left = mid;
			}
			else {
				right = mid;
			}
		}
		return right;
	}

};

//二次元のビット、未AC
class Bit2 {
public:
	int h, w;
	vll bit;
	Bit2(int _h, int _w) {
		h = _h; w = _w;
		bit.resize(h + 1);
		for (int i = 0; i <= h; i++) bit[i].resize(w + 1);
	}

	ll sum(int i, int j) {
		ll s = 0;
		while (i > 0) {
			int j0 = j;
			while (j0 > 0) {
				s += bit[i][j0];
				j0 -= j0 & -j0;
			}
			i -= i & -i;
		}
		return s;
	}

	void add(int i, int j, ll x) {
		int i0 = i;
		while (i0 <= h) {
			int j0 = j;
			while (j0 <= w) {
				bit[i0][j0] += x;
				j0 += j0 & -j0;
			}
			i0 += i0 &-i0;
		}
	}
};


int main() {
	int q, i;
	cin >> n >> q;
	bit.resize(n + 1);
	for (i = 1; i <= n; i++) {
		int a;
		cin >> a;
		add(i, a);
	}
	for (int unko = 0; unko < q; unko++) {
		int t, l, r;
		cin >> t >> l >> r;
		if (t == 1) {
			cout << sum(r) - sum(l - 1) << endl;
		}
		else {
			add(l, r);
		}
	}
}