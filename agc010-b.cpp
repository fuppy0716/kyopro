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

int main() {
	ll n, i, j;
	cin >> n;
	vl a(n);
	ll sum = 0;
	for (i = 0; i<n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	if (sum % (n*(n + 1) / 2) != 0) {
		cout << "NO" << endl;
		return 0;
	}
	ll m = sum / (n*(n + 1) / 2);
	vl num(n);
	for (i = 1; i<n; i++) {
		ll sa = a[i] - a[i - 1];
		if ((m - sa) % n != 0 || m - sa < 0) {
			cout << "NO" << endl;
			return 0;
		}
		num[i - 1] = (m - sa) / n;
	}
	ll sa = a[0] - a[n - 1];
	if ((m - sa) % n != 0 || m - sa < 0) {
		cout << "NO" << endl;
		return 0;
	}
	num[n - 1] = (m - sa) / n;

	ll ans = 0;
	for (i = 0; i<n; i++) {
		ans += num[i];
	}
	if (ans == m) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}

	return 0;
}