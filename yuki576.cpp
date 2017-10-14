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
#define pll pair<ll,ll>
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
	int n, k, i, j;
	scanf("%d%d", &n, &k);
	char c;
	vector<double> a(n);
	for (i = 0; i < n; i++) {
		scanf(" %c", &c);
		if (c == '0') {
			a[i] = 0;
		}
		else {
			a[i] = 1;
		}
	}
	a.insert(a.end(), a.begin(), a.end());
	//DEBUG_VEC(a);
	double left = 0, right = 1, ans = 0;
	while (left + 0.00000005 < right) {
		double x = (left + right) / 2;
		vector<double> b = a;
		for (i = 0; i < 2 * n; i++) {
			b[i] -= x;
		}
		//DEBUG_VEC(b);
		vector<double> sum(2 * n + 1);
		sum[0] = 0;
		for (i = 0; i < 2 * n; i++) {
			sum[i + 1] = sum[i] + b[i];
		}
		//DEBUG_VEC(sum);
		deque<int> dq;
		for (i = k; i < n; i++) {
			while (!dq.empty() && sum[dq[dq.size() - 1]] <= sum[i]) {
				dq.pop_back();
			}
			dq.push_back(i);
		}
		/*
		for (i = 0; i < dq.size(); i++) {
		printf("%d ", dq[i]);
		}
		printf("\n");
		*/
		bool flag = false;
		for (i = 0; i < n; i++) {
			while (!dq.empty() && sum[dq[dq.size() - 1]] <= sum[i + n]) {
				dq.pop_back();
			}
			dq.push_back(i + n);
			while (dq[0] < i + k) {
				dq.pop_front();
			}
			if (sum[dq[0]] >= sum[i]) {
				flag = true;
			}
			if (flag) {
				break;
			}
		}
		if (flag) {
			left = x + 0.00000005;
			ans = x;
		}
		else {
			right = x;
		}
	}
	Sp(ans);
}