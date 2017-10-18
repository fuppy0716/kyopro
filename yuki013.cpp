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

#define W 105
#define H 105
vii M(H, vi(W));
vii C(H, vi(W, -1));
int cnt = 0;
int w, h;

bool bfs(int i0, int j0) {
	pii now = make_pair(i0, j0);
	queue<pii> q;
	q.push(now);
	C[i0][j0] = ++cnt;
	while (!q.empty()) {
		now = q.front();
		q.pop();
		int i = now.first, j = now.second;
		int num = 0;
		for (int k = 0; k < 4; k++) {
			if (C[i + dy[k]][j + dx[k]] == cnt) {
				num++;
			}
		}
		if (num >= 2) {
			return true;
		}
		for (int k = 0; k < 4; k++) {
			if (C[i + dy[k]][j + dx[k]] == -1 && M[i + dy[k]][j + dx[k]] == M[i][j]) {
				C[i + dy[k]][j + dx[k]] = cnt;
				q.push(make_pair(i + dy[k], j + dx[k]));
			}
		}
	}
	return false;
}

int main() {
	int i, j;
	scanf("%d%d", &w, &h);
	for (i = 1; i <= h; i++) {
		for (j = 1; j <= w; j++) {
			scanf("%d", &M[i][j]);
		}
	}
	for (i = 1; i <= h; i++) {
		for (j = 1; j <= w; j++) {
			if (C[i][j] == -1) {
				if (bfs(i, j)) {
					cout << "possible" << endl;
					return 0;
				}
			}
		}
	}
	cout << "impossible" << endl;
	return 0;
}