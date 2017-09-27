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
	ll n, t, i, j;
	cin >> n >> t;
	vl a(n);
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	int cnt = 0;
	ll m = inf, M = -1;
	ll sa = M - m;
	for (i = 0; i < n; i++) {
		if (m > a[i]) {
			m = a[i];
			M = -1;
		}
		if (M < a[i]) {
			M = a[i];
			if (sa < M - m) {
				sa = M - m;
				cnt = 1;
			}
			else if (sa == M - m) {
				cnt++;
			}
		}
	}
	cout << cnt << endl;

}