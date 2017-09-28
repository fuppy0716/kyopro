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
	int n, i, j;
	cin >> n;
	vl a(3 * n);
	for (i = 0; i < 3 * n; i++) {
		cin >> a[i];
	}
	priority_queue<ll> b;
	priority_queue<ll, vector<ll>, greater<ll> > f;
	vl M(3 * n), m(3 * n);
	for (i = 0; i < n; i++) {
		M[n] += a[i];
		f.push(a[i]);
	}
	for (i = n + 1; i <= 2 * n; i++) {
		f.push(a[i - 1]);
		M[i] = M[i - 1] + a[i - 1] - f.top();
		//cout << f.top() << endl;
		f.pop();
	}
	for (i = 2 * n; i < 3 * n; i++) {
		m[2 * n] += a[i];
		b.push(a[i]);
	}
	for (i = 2 * n - 1; i >= n; i--) {
		b.push(a[i]);
		m[i] = m[i + 1] + a[i] - b.top();
		//cout << b.top() << endl;
		b.pop();
	}
	/*
	for (i = n; i <= 2*n; i++) {
	cout << M[i] << " " << m[i] << endl;
	}*/

	ll ans = -INF;
	for (i = n; i <= 2 * n; i++) {
		ans = max(ans, M[i] - m[i]);
	}
	cout << ans << endl;
}