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

string s;
int n;
vector<pll> has;
vl dp(10010, -1);

#define MAXN 10020
//B1, B2:二つの基数　M: modをとる
const ll B1 = 100000007;
const ll B2 = 103;
const ll M = 1000000009;
vector<ll> Bpower1(MAXN);
vector<ll> Bpower2(MAXN);
vector<ll> Bpower_inv1(MAXN);
vector<ll> Bpower_inv2(MAXN);

ll mod_pow(ll x, ll p, ll M) {
	ll a = 1;
	while (p) {
		if (p % 2)
			a = a*x%M;
		x = x*x%M;
		p /= 2;
	}
	return a;
}

ll mod_inverse(ll a, ll m) {
	return mod_pow(a, m - 2, m);
}

void build_bpower() {
	Bpower1[0] = 1;
	for (int j = 1; j < MAXN; j++) {
		Bpower1[j] = Bpower1[j - 1] * B1 % M;
	}
	Bpower2[0] = 1;
	for (int j = 1; j < MAXN; j++) {
		Bpower2[j] = Bpower2[j - 1] * B2 % M;
	}
	for (int j = 0; j < MAXN; j++) {
		Bpower_inv1[j] = mod_inverse(Bpower1[j], M);
		Bpower_inv2[j] = mod_inverse(Bpower2[j], M);
	}
}

//sのハッシュ値を求める
//rh[i] = s[i]*(b^(n - i - 1)) + s[i + 1]*(b^(n - i - 2)) + ... + s[n - 1] * b^0;
vector<pll> rolling_hash(string s) {
	vector<pll> rh(s.size() + 1);
	rh[s.size()].first = rh[s.size()].second = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		rh[i].first = (rh[i + 1].first + s[i] * Bpower1[s.size() - i - 1]) % M;
		rh[i].second = (rh[i + 1].second + s[i] * Bpower2[s.size() - i - 1]) % M;
	}
	return rh;
}

//hashに対応する文字列のi文字目からl文字ののハッシュ値を求める
//しょっちゅう呼び出す場合は、時間がかかるため本文に直接コピペ
pll part(vector<pll> hash, int i, int l) {
	pll h = pll(hash[i].first - hash[i + l].first, hash[i].second - hash[i + l].second);
	h.first += M; h.second += M;
	h.first %= M; h.second %= M;
	h.first = h.first * Bpower_inv1[hash.size() - 1 - i - l] % M;
	h.second = h.second * Bpower_inv2[hash.size() - 1 - i - l] % M;
	return h;
}

ll dfs(int i) {
	if (dp[i] != -1) {
		return dp[i];
	}
	if (n % 2 && i == n / 2) {
		dp[i] = 1;
		return 1;
	}
	ll res = 1;
	for (int left = i, right = n - 1 - i; left < right; left++, right--) {
		pll h1 = pll(has[i].first - has[i + left - i + 1].first, has[i].second - has[i + left - i + 1].second);
		h1.first += M; h1.second += M;
		h1.first %= M; h1.second %= M;
		h1.first = h1.first * Bpower_inv1[has.size() - 1 - i - left + i - 1] % M;
		h1.second = h1.second * Bpower_inv2[has.size() - 1 - i - left + i - 1] % M;
		pll h2 = pll(has[right].first - has[right + left - i + 1].first, has[right].second - has[right + left - i + 1].second);
		h2.first += M; h2.second += M;
		h2.first %= M; h2.second %= M;
		h2.first = h2.first * Bpower_inv1[has.size() - 1 - right - left + i - 1] % M;
		h2.second = h2.second * Bpower_inv2[has.size() - 1 - right - left + i - 1] % M;
		if (h1 == h2) {
			res += dfs(left + 1);
			res %= MOD;
		}
	}
	dp[i] = res;
	return res;
}

int main() {
	cin >> s;
	n = s.size();
	build_bpower();
	has = rolling_hash(s);
	ll ans = dfs(0);
	cout << ans << endl;
}
