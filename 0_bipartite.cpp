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
#define N 100010
vii M(N, vi());
ll n, m;
vi color(N, -1);
//�񕔃O���t���ǂ����𔻒f
bool bipartite() {
	stack<int> st;
	color[0] = 0;
	st.push(0);
	int i, j;
	while (!st.empty()) {
		i = st.top();
		st.pop();
		for (j = 0; j < M[i].size(); j++) {
			if (color[M[i][j]] == color[i]) {
				//cout << "NO" << endl;
				return false;
			}
			else {
				if (color[M[i][j]] == -1) {
					color[M[i][j]] = 1 - color[i];
					st.push(M[i][j]);
				}
			}
		}
	}
	//cout << "YES" << endl;
	return true;
}

int main() {
	int i, j;
	scanf("%lld%lld", &n, &m);
	int a, b;

	for (i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		a--; b--;
		M[a].push_back(b);
		M[b].push_back(a);
	}
	bool flag = bipartite();
	if (flag) {
		ll w = 0, b = 0;
		for (i = 0; i < n; i++) {
			if (color[i] == 0) {
				w++;
			}
			else {
				b++;
			}
		}
		cout << w*b - m << endl;
		return 0;
	}
	else {
		cout << (n*n - n) / 2 - m << endl;
		return 0;
	}
}