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

void print_bit(ll n, ll k) {
	ll m = (1LL << (k - 1));
	while (m >= 1) {
		if ((n&m)) {
			cout << 1;
		}
		else {
			cout << 0;
		}
		m >>= 1;
	}
	return;
}


int main() {
	int l, m, n, i0;
	cin >> l >> m >> n;
	vi a(l), b(m);
	for (i0 = 0; i0 < l; i0++) {
		cin >> a[i0];
	}
	for (i0 = 0; i0 < m; i0++) {
		cin >> b[i0];
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	//DEBUG_VEC(a);
	//DEBUG_VEC(b);
	vl x(n / 32 + 2), y(n / 32 + 2);
	int ai = 0, bi = 0;
	for (int i = 0;; i++) {
		if (i * 32 > n) {
			break;
		}
		for (int j = 0; j < 32; j++) {
			int z = i * 32 + j;
			if (ai < l) {
				if (a[ai] == z) {
					x[i] |= (1LL << j);
				}
				if (a[ai] <= z) {
					ai++;
				}
			}
			if (bi < m) {
				if (b[bi] == z) {
					y[i] |= (1LL << j);
				}
				if (b[bi] <= z) {
					bi++;
				}
			}
		}
	}
	//DEBUG_VEC(x);
	//DEBUG_VEC(y);

	vi bitstand(1 << 16);
	for (i0 = 0; i0 < (1 << 16); i0++) {
		int cnt = 0;
		int temp = 1;
		for (int i = 0; i < 16; i++) {
			if (i0 & temp) {
				cnt++;
			}
			temp <<= 1;
		}
		bitstand[i0] = cnt;
	}

	int q;
	cin >> q;
	int length = x.size();
	for (i0 = 0; i0 < q; i0++) {
		int i, j;
		for (i = length - 1; i >= 0; i--) {
			//print_bit(y[i], 64);
		}
		//cout << endl;
		int ans = 0;
		for (i = 0; i < length; i++) {
			ll temp = x[i] & y[i];
			ll mask = (1 << 16) - 1;
			for (j = 0; j < 2; j++) {
				ll bit = temp & mask;
				ans += bitstand[bit];
				temp >>= 16;
			}
		}
		ll mask = 1 << 31;
		for (i = length - 1; i >= 0; i--) {
			y[i] = (y[i] & (mask - 1)) << 1;
			if (i != 0) {
				if (y[i - 1] & mask) {
					y[i] |= 1ULL;
				}
			}
		}
		cout << ans << endl;
	}
}

/*
100 100 100
52 21 91 38 1 8 3 20 17 73 14 82 26 88 25 89 72 56 11 55 9 62 51 32 66 97 58 75 61 74 4 84 86 100 64 87 69 78 54 45 34 7 81 60 98 23 2 16 18 6 5 41 63 57 96 36 99 27 53 30 39 10 42 12 35 92 28 33 50 83 90 22 71 93 15 13 77 70 46 80 67 29 95 24 37 47 68 59 19 44 79 40 65 48 43 85 31 94 76 49
53 89 78 21 97 44 40 43 86 26 95 82 57 60 66 42 75 45 4 77 91 9 7 90 2 58 51 12 16 27 13 71 52 30 50 8 84 83 65 5 54 85 55 99 6 24 14 47 28 11 76 64 56 1 34 29 3 48 17 33 87 15 94 46 62 70 35 41 68 18 32 96 100 23 25 88 49 73 31 37 59 69 22 98 20 19 92 38 80 79 81 39 67 74 36 63 72 93 61 10
1

50 50 150
92 135 12 87 104 130 21 38 60 81 80 145 29 120 52 136 66 57 133 22 1 15 56 111 93 137 114 116 97 115 37 28 32 122 17 113 73 101 100 98 138 127 109 144 91 36 74 134 72 88
11 25 60 56 75 39 38 8 12 90 9 63 2 58 80 94 28 45 31 34 100 13 88 35 85 3 54 43 40 71 19 21 69 98 66 73 65 46 52 84 77 17 59 67 4 99 7 51 62 83
150
*/