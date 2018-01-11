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
int n, m;
int ans = 0;

map<ll, int> mp;
vii G(42, vi());


//n‚Ìkbit•\Œ»‚ð•\Ž¦‚·‚é
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
	cout << endl;
}

int dfs(ll can, int now, int cnt, ll mask) {
	//print_bit(mask, 42);
	if (now == -1) {
		return cnt;
	}
	if (mp[can&mask]) {
		return cnt + mp[can&mask];
	}
	if (!(can & (1LL << now))) {
		return dfs(can, now - 1, cnt, mask >> 1);
	}
	ll can2 = can;
	for (int i = 0; i < G[now].size(); i++) {
		ll temp = 1LL << (G[now][i]);
		can2 &= ~temp;
	}
	int res = dfs(can2, now - 1, cnt + 1, mask >> 1);
	res = max(res, dfs(can, now - 1, cnt, mask >> 1));
	mp[can & mask] = max(mp[can & mask], res - cnt);
	return res;
}

int main() {
	int i, j;
	cin >> n >> m;
	for (i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	ll can = (1LL << n) - 1;
	ll mask = (1LL << n) - 1;
	int ans = dfs(can, n - 1, 0, mask);
	cout << ans << endl;
}