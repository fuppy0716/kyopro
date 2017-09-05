
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
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };

int main() {
	int b, c, d;
	cin >> b >> c >> d;
	if (b > c) {
		swap(b, c);
	}
	if (b > d) {
		swap(b, d);
	}
	if (c > d) {
		swap(c, d);
	}
	int n, i, j;
	cin >> n;
	vi e(4, 0);
	for (i = 0; i < n; i++) {
		int a;
		cin >> a;
		if (a < b) {
			e[0]++;
		}
		else if (a < c) {
			e[1]++;
		}
		else if (a < d) {
			e[2]++;
		}
		else {
			e[3]++;
		}
	}
	ll ans = pow(2, n);
	ans -= pow(2, e[0] + e[1] + e[2]);
	ans -= e[3] * pow(2, e[0] + e[1]);
	ans -= (e[3] * (e[3] - 1)) / 2 * pow(2, e[0]);
	ans -= e[3] * e[2] * pow(2, e[0]);
	cout << ans << endl;

}