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
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define MAXN 100050
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

//ローリングハッシュには特に関係ないよ
bool cmp(string s1, string s2) {
	if (s1.size() < s2.size()) {
		return true;
	}
	else if (s1.size() > s2.size()) {
		return false;
	}
	else {
		return (s1 < s2);
	}
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

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, i, j;
	cin >> n;
	vs s(n);
	set<int> st;
	for (i = 0; i < n; i++) {
		cin >> s[i];
		st.insert(s[i].size());
	}
	sort(s.begin(), s.end(), cmp);
	vi num;
	for (auto itr = st.begin(); itr != st.end(); itr++) {
		num.push_back(*itr);
	}
	build_bpower();

	string t;
	cin >> t;
	int m = t.size();

	vector<pll> thash = rolling_hash(t);;
	vector<set<pll> > shash(num.size());
	int pre = 0;
	int numi = -1;
	for (i = 0; i < n; i++) {
		if (pre != s[i].size()) {
			numi++;
			pre = s[i].size();
		}
		auto tmp = rolling_hash(s[i]);
		shash[numi].insert(tmp[0]);
	}


	vl dp(m + 1);
	dp[0] = 1;
	for (i = 0; i < m; i++) {
		for (j = 0; j < num.size(); j++) {
			if (i + num[j] > m) {
				break;
			}
			pll th = pll(thash[i].first - thash[i + num[j]].first, thash[i].second - thash[i + num[j]].second);
			th.first += M;
			th.first %= M;
			th.second += M;
			th.second %= M;
			th.first = th.first * Bpower_inv1[m - i - num[j]] % M;
			th.second = th.second * Bpower_inv2[m - i - num[j]] % M;
			if (shash[j].count(th)) {
				dp[i + num[j]] = (dp[i + num[j]] + dp[i]) % MOD;
			}
		}
	}
	cout << dp[m] << endl;
}