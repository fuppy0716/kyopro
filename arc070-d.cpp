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
	int n, k, i, j;
	scanf("%d%d", &n, &k);
	vi a;
	for (i = 0; i < n; i++) {
		int b;
		scanf("%d", &b);
		if (b < k) {
			a.push_back(b);
		}
	}
	int ans = 0;
	n = a.size();
	sort(a.begin(), a.end());
	int left = 0, right = n;
	while (left < right) {
		int i0 = (right + left) / 2;
		vii dp(n + 1, vi(k + 1));
		dp[0][0] = 1;
		for (i = 0; i < n; i++) {
			for (j = 0; j <= k; j++) {
				if (dp[i][j]) {
					if (j + a[i] <= k && i != i0) {
						dp[i + 1][j + a[i]] = 1;
					}
					dp[i + 1][j] = 1;
				}
			}
		}
		bool flag = false;
		for (j = k - a[i0]; j < k; j++) {
			if (dp[n][j]) {
				flag = true;
				break;
			}
		}
		if (flag) {
			right = i0;
		}
		else {
			left = i0 + 1;
		}
	}
	cout << left << endl;
}