
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

vi ans;

void f(int l, int r) {
	if (l == r) {
		ans.push_back(l);
		return;
	}
	else if (l > r) {
		return;
	}
	else {
		int md = (l + r) / 2;
		ans.push_back(md);
		f(l, md - 1);
		f(md + 1, r);
	}
}

int main() {
	int k, i;
	cin >> k;
	int n = 1;
	for (i = 0; i < k; i++) {
		n *= 2;
	}
	n--;
	ans.push_back(1);
	f(2, n);
	for (i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
}