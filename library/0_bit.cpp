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

/*
xの一番下に立っているビットの求め方
x & -x;

*/


//nのkbit表現を表示する
void print_bit(ll n, ll k) {
	ll m = (1LL << (k - 1));;
	while (m >= 1) {
		if ((n&m)) {
			cout << 1;
		}
		else {
			cout << 0;
		}
		m >>= 1;
	}
	cout << endl;
}

//nのビット表現の部分集合を列挙する。
void part(ll n) {
	ll m = n;
	do {
		print_bit(m, 8); //部分集合に対する処理
		m = (m - 1)&n;
	} while (m != n);
}

//{0,1,...,n-1}に含まれるサイズkの部分集合を列挙
void part_size(ll n, ll k) {
	int comb = (1LL << k) - 1;
	while (comb < 1LL << n) {
		print_bit(comb, 12);
		int x = comb & -comb, y = comb + x;
		comb = ((comb & ~y) / x >> 1) | y;
	}
}



int main() {
	part(45);
	cout << endl << endl;
	part_size(10, 4);
}










#include <random>
ll r, b, c;
vl m, s, p;



void solve1() {
	ll ans = INF;
	rep(syugou, (1LL << c)) {
		if (syugou == 0) {
			continue;
		}
		vector<bool> use(c, false);
		int cnt0 = 0;
		rep(k, c) {
			if ((syugou & (1LL << k))) {
				use[k] = true;
				cnt0++;
			}
		}
		if (cnt0 > r) {
			continue;
		}
		vl time(c);
		vi cnt(c);
		bool flag = true;
		rep(aaa, b) {
			pii mi = pii(inf, inf);
			rep(i, c) {
				if (!use[i]) {
					continue;
				}
				if (cnt[i] == m[i]) {
					continue;
				}
				if (time[i] == 0) {
					mi = min(mi, pii(s[i] + p[i], i));
				}
				else {
					mi = min(mi, pii(time[i] + s[i], i));
				}
			}
			if (mi.second >= inf) {
				flag = false;
				break;
			}
			if (time[mi.second] == 0) {
				time[mi.second] = s[mi.second] + p[mi.second];
			}
			else {
				time[mi.second] += s[mi.second];
			}
			cnt[mi.second]++;
		}
		if (!flag) {
			continue;
		}
		ll res = -1;
		rep(i, c) {
			if (!use[i]) {
				continue;
			}
			res = max(res, time[i]);
		}
		ans = min(ans, res);
	}
	cout << ans << endl;
}

int main() {
	/*
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand100(0, 99);
	//*/
	int t;
	scanf("%d", &t);
	rep1(cas, t) {
		cin >> r >> b >> c;
		m.resize(c); s.resize(c); p.resize(c);
		rep(i, c) {
			cin >> m[i] >> s[i] >> p[i];
		}
		printf("Case #%d: ", cas);
		solve1();
	}
}






int main() {
	int t;
	scanf("%d", &t);
	rep1(cas, t) {
		ll n;
		double p;
		cin >> n >> p;
		vl h(n), w(n);
		ll base = 0;
		bool flagh = true, flagw = true;
		rep(i, n) {
			cin >> h[i] >> w[i];
			base += 2 * (h[i] + w[i]);
		}
		printf("Case #%d: ", cas);
		double ans = base;
		double addmi = 0, addma = 0;
		rep(i, n) {
			addmi += 2 * min(h[i], w[i]);
			addma += 2 * sqrt(h[i] * h[i] + w[i] * w[i]);
			if (base + addmi <= p && p <= base + addma) {
				ans = p;
				break;
			}
			else {
				if (base + addma <= p) {
					if (abs(p - ans) > (p - (base + addma))) {
						ans = base + addma;
					}
				}
			}
		}
		Sp(ans);
	}
}