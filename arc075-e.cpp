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
	vl a(n);
	vl sum(n + 1);
	for (i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
		a[i] -= k;
		sum[i + 1] = sum[i] + a[i];
	}
	int b = sqrt(n);
	vll sum2;
	i = 0;
	while (i <= n) {
		sum2.push_back(vl());
		for (j = 0; j < b; j++) {
			sum2[sum2.size() - 1].push_back(sum[i]);
			i++;
			if (i > n)
				break;
		}
	}

	for (i = 0; i < sum2.size(); i++) {
		sort(sum2[i].begin(), sum2[i].end());
	}
	ll cnt = 0;
	for (i = 0; i < n; i++) {
		for (j = i + 1; (j <= n) && (j%b != 0); j++) {
			if (sum[j] - sum[i] >= 0) {
				cnt++;
			}
		}
		for (j = i / b + 1; j < sum2.size(); j++) {
			cnt += (sum2[j].end() - lower_bound(sum2[j].begin(), sum2[j].end(), sum[i]));
		}
	}
	printf("%lld\n", cnt);
}