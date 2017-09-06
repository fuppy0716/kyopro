//ノードのつながりが行列の図で与えられた場合

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

//t時刻、d[v]vを最初に発見した時刻、f[v]vを調べ終わった時刻
static const int H = 510, W = 510;
int t = 0;
vector< vector<char> > M(H, vector<char>(W, '#'));
vii d(H, vi(W, -1)), f(H, vi(W, -1));

void dfs(pii now) {
	int i;
	for (i = 0; i < 4; i++) {
		if (M[now.first + dx[i]][now.second + dy[i]] == '.' || M[now.first + dx[i]][now.second + dy[i]] == 'g') {
			M[now.first + dx[i]][now.second + dy[i]] = '-';
			d[now.first + dx[i]][now.second + dy[i]] = ++t;
			dfs(make_pair(now.first + dx[i], now.second + dy[i]));
		}
	}
	M[now.first][now.second] = '#';
	f[now.first][now.second] = ++t;
}

int main() {
	int h, w, i, j;
	cin >> h >> w;
	pii start, goal;
	for (i = 1; i <= h; i++) {
		for (j = 1; j <= w; j++) {
			cin >> M[i][j];
			if (M[i][j] == 's') {
				start.first = i;
				start.second = j;
			}
			else if (M[i][j] == 'g') {
				goal.first = i;
				goal.second = j;
			}
		}
	}
	M[start.first][start.second] = '-';
	d[start.first][start.second] = t;
	dfs(start);
	if (d[goal.first][goal.second] != -1) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}