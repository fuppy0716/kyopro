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
	int n, c, v, i, j;
	cin >> n;
	cin >> c >> v;
	vl dp(2 * n - 1, INF);
	dp[0] = dp[1] = 0;
	ll m;
	for (i = 1; i < n; i++) {
		for (j = i * 2; j <= 2 * n - 2; j += i) {
			dp[j] = min(dp[j], dp[i] + c + v*(j - i) / i);
		}
	}
	m = INF;
	for (i = n; i <= 2 * n - 2; i++) {
		m = min(m, dp[i]);
	}
	cout << m << endl;
}