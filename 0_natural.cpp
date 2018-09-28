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

ll gcd(ll a, ll b) {
	if (b > a) {
		swap(a, b);
	}
	ll r = a%b;
	while (r != 0) {
		a = b;
		b = r;
		r = a%b;
	}
	return b;
}

ll lcm(ll a, ll b) {
	return (a / gcd(a, b))*b;
}

//ax + by = gcd(a, b) となるx, yをもとめる
ll extgcd(ll a, ll b, ll& x, ll& y) {
	ll d = a;
	if (b != 0) {
		d = extgcd(b, a%b, y, x);
		y -= (a / b)*x;
	}
	else {
		x = 1; y = 0;
	}
	return d;
}


//中国剰余定理
//modの積がすごいときオーバーフローする。
//am[i].first:a_i, am[i].second:m_i
//return (x, y) y = lcm(m1, m2, ..., m_n),  x%m_i = a_i
typedef __int128 lll;
pll crt(vector<pll> am) {
	rep(i, am.size() - 1) {
		ll g, x, y, z;
		am[i].first = (am[i].first % am[i].second + am[i].second) % am[i].second;
		am[i + 1].first = (am[i + 1].first % am[i + 1].second + am[i + 1].second) % am[i + 1].second;
		g = extgcd(am[i].second, am[i + 1].second, x, y);
		if (am[i].first%g != am[i].second%g) return pll(-1, 0); //解なし
		lll lcm = (lll)am[i].second*(am[i + 1].second / g);
		if (lcm < am[i].second) return pll(-2, 0); //オーバーフロー
		ll mo = am[i + 1].second = lcm;
		lll v = am[i].first + ((lll)(am[i].second / g) * x % mo * (am[i + 1].first - am[i].first + mo) % mo);
		am[i + 1].first = (v%mo + mo) % mo;
	}
	return am.back();
}

void prime(vector<bool> &isprime /*, vll &soinsu */) {
	ll i, j;
	isprime[0] = isprime[1] = false;
	for (i = 2; i < isprime.size(); i++) {
		if (isprime[i]) {
          // soinsu[i].push_back(i);
			for (j = 2; i*j < isprime.size(); j++) {
				isprime[i*j] = false;
                /*
				soinsu[i * j].push_back(i);
				int temp = i * j;
				while (temp % i == 0) {
					temp /= i;
				}
                */
			}
		}
	}
}

//n以下のnと互いに素な自然数の個数
//O(sqrt(n))
int eulerSingle(int n) {
	int res = n;
	for (int i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			res = res / i * (i - 1);
			for (; n%i == 0; n /= i);
		}
	}
	if (n != 1) res = res / n * (n - 1);
	return res;
}


//オイラー関数の値のテーブル
//O(n)
vl euler(n + 1);
void eulerTable(int n) {
	for (i = 0; i <= n; i++) {
		euler[i] = i;
	}
	for (i = 2; i <= n; i++) {
		if (euler[i] == i) {
			for (j = i; j <= n; j += i) {
				euler[j] = euler[j] / i * (i - 1);
			}
		}
	}
}


int main() {
	ll n;
	int i, j;
	cin >> n;
	vl t(n);
	for (i = 0; i < n; i++) {
		cin >> t[i];
	}
	ll ans = 1;
	for (i = 0; i < n; i++) {
		ans = lcm(ans, t[i]);
	}
	cout << ans << endl;
}
