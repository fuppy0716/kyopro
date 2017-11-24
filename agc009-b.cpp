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
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define N 100000
vi d(N, inf);
vii M(N, vi());


int dfs(int s) {
	vi a;
	for (int i = 0; i < M[s].size(); i++) {
		a.push_back(dfs(M[s][i]) + 1);
	}
	sort(a.begin(), a.end());
	int res = 0;
	for (int i = 0; i < a.size(); i++) {
		res = max(res, a[i] + (int)a.size() - 1 - i);
	}
	return res;
}


int main() {
	int n, i;
	cin >> n;
	for (i = 1; i < n; i++) {
		int a;
		cin >> a;
		a--;
		M[a].push_back(i);
	}
	cout << dfs(0) << endl;
}