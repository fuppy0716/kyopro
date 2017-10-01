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
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

/*
cin.tie(0);
ios::sync_with_stdio(false);
*/
int main() {
	int n;
	cin >> n;
	if (n == 1 || n == 2) {
		cout << 1 << " " << 1 << endl;
	}
	else if (n == 3) {
		cout << 2 << " " << 32 << endl;
	}
	else if (n == 4) {
		cout << 2 << " " << 18 << endl;
	}
	else {
		cout << 2 << " " << 4 << endl;
	}
	return 0;
	/*
	ll m = pow(2, n*n);
	ll i, i2, j, k, l;
	ll cnt = 0;
	for (i2 = 0; i2 < m; i2++) {
	vii hyou(n, vi(n));
	for (j = 0; j < n; j++) {
	for (k = 0; k < n; k++) {
	ll judge = n*j + k;
	if ((i2&(ll)pow(2,judge)) != 0) {
	hyou[j][k] = 1;
	}
	}
	}
	bool flag = true;
	for (i = 0; i + 2 < n; i++) {
	for (j = 0; j < n; j++) {
	if (hyou[i][j] == hyou[i + 1][j] && hyou[i][j] == hyou[i + 2][j]) {
	flag = false;
	}
	}
	}

	for (i = 0; i + 2 < n; i++) {
	for (j = 0; j < n; j++) {
	if (hyou[j][i] == hyou[j][i+1] && hyou[j][i] == hyou[j][i+2]) {
	flag = false;
	}
	}
	}
	for (i = 0; i + 2 < n; i++) {
	for (j = 0; j + 2 < n; j++) {
	if (hyou[i][j] == hyou[i + 1][j + 1] && hyou[i][j] == hyou[i + 2][j + 2]) {
	flag = false;
	}
	}
	}
	for (i = 0; i + 2 < n; i++) {
	for (j = 2; j < n; j++) {
	if (hyou[i][j] == hyou[i + 1][j - 1] && hyou[i][j] == hyou[i + 2][j - 2]) {
	flag = false;
	}
	}
	}
	if (flag) {
	cnt++;
	}
	}
	cout << cnt << endl;
	*/
}