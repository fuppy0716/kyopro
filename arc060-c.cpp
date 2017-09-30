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
int main() {
int n, a, i, j, k;
cin >> n >> a;
vi x(n);
for (i = 0; i < n; i++) {
cin >> x[i];
}
vector< vll > dp(n + 1, vll(n + 1, vl(2501, 0)));
dp[0][0][0] = 1;
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
for (k = 0; k <= 2500; k++) {
if (dp[i][j][k] != 0) {
dp[i + 1][j][k] += dp[i][j][k];
dp[i + 1][j + 1][k + x[i]] += dp[i][j][k];
}
}
}
}
ll sum = 0;
for (j = 1; j <= n; j++) {
sum += dp[n][j][a*j];
}
cout << sum << endl;
}
*/

int main() {
	int n, a, i, j, k;
	cin >> n >> a;
	vi x(n);
	for (i = 0; i < n; i++) {
		cin >> x[i];
		x[i] -= a;
	}
	vll dp(n + 1, vl(5010));
	dp[0][2500] = 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 5010; j++) {
			if (dp[i][j] != 0) {
				dp[i + 1][j] += dp[i][j];
				dp[i + 1][j + x[i]] += dp[i][j];
			}
		}
	}
	cout << dp[n][2500] - 1 << endl;
}