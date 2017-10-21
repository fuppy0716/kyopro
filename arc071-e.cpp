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
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	string s, t;
	cin >> s;
	cin >> t;
	int n = s.size(), m = t.size();
	vector<pii> sum_s(n + 1), sum_t(m + 1);
	sum_s[0] = sum_t[0] = pii(0, 0);
	int i0;
	for (i0 = 0; i0 < n; i0++) {
		sum_s[i0 + 1] = sum_s[i0];
		if (s[i0] == 'A') {
			sum_s[i0 + 1].first++;
		}
		else {
			sum_s[i0 + 1].second++;
		}
	}
	for (i0 = 0; i0 < m; i0++) {
		sum_t[i0 + 1] = sum_t[i0];
		if (t[i0] == 'A') {
			sum_t[i0 + 1].first++;
		}
		else {
			sum_t[i0 + 1].second++;
		}
	}
	int q;
	cin >> q;
	for (i0 = 0; i0 < q; i0++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		int x, y;
		x = (sum_s[b].first - sum_s[a - 1].first) - (sum_s[b].second - sum_s[a - 1].second);
		y = (sum_t[d].first - sum_t[c - 1].first) - (sum_t[d].second - sum_t[c - 1].second);
		if ((x - y) % 3 == 0) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}

}