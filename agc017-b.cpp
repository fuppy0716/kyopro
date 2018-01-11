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
	int n, k;
	ll a2, b2, c, d;
	cin >> n >> a2 >> b2 >> c >> d;
	ll a = min(a2, b2);
	ll b = max(a2, b2);
	if (b - a > d*(n - 1)) {
		cout << "NO" << endl;
		return 0;
	}
	if (b - a >= c*(n - 1)) {
		cout << "YES" << endl;
		return 0;
	}
	for (k = 0; k < n; k++) {
		ll m = c*k - d*(n - 1 - k);
		ll M = d*k - c*(n - 1 - k);
		if (a + m <= b && a + M >= b) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
}