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

/*
cin.tie(0);
ios::sync_with_stdio(false);
*/
int main() {
	ll n, k, i, j;
	cin >> n >> k;
	vl a(n), b(n);
	for (i = 0; i < n; i++) {
		int a2, b2;
		cin >> a2 >> b2;
		if (a2 > k) {
			continue;
		}
		a.push_back(a2);
		b.push_back(b2);
	}
	n = a.size();
	j = k;
	ll m = 0;
	vector<bool> k2;
	while (j > 0) {
		k2.push_back((bool)(j & 1));
		j >>= 1;
		m++;
	}
	//DEBUG_VEC(k2);
	//cout << m << endl;

	ll ans = -1;
	vector<bool> used(n, true);
	bool flag = true;
	if (m == 0 || m == 1) {
		flag = false;
	}
	while (flag) {
		ll sum = 0;
		while (!k2[m - 1]) {
			m--;
		}
		if (m == 1) {
			break;
		}
		ll m2 = m - 1;
		while (!k2[m2 - 1]) {
			m2--;
			if (m2 == 0) {
				flag = false;
				break;
			}
		}
		ll out = pow(2, m - 1);
		for (i = 0; i < n; i++) {
			if (used[i] && ((a[i] & (ll)pow(2, m) - 1) < out)) {
				sum += b[i];
			}
			for (j = m2 + 1; j < m; j++) {
				if (((ll)pow(2, j - 1)&a[i]) != 0) {
					used[i] = false;
				}
			}
		}
		ans = max(ans, sum);
		m--;

	}
	ll sum = 0;
	for (i = 0; i < n; i++) {
		if ((a[i] | k) <= k) {
			sum += b[i];
		}
	}
	ans = max(ans, sum);
	cout << ans << endl;


}