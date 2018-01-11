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
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;
static const int N = 400020;

vector< vector<pll> > adj(N, vector<pll>());
vl d(N, INF);
map<ll, ll> mp[N];
int cnt = 1;


void dijkstra() {
	priority_queue<pll, vector<pll>, greater<pll> > pq;
	int i;
	vi color(cnt, WHITE);

	d[1] = 0;
	pq.push(make_pair(0, 1));
	color[1] = GRAY;

	while (!pq.empty()) {
		pll f = pq.top();
		pq.pop();
		ll u = f.second;
		color[u] = BLACK;
		if (d[u]<f.first) {
			continue;
		}
		for (i = 0; i < adj[u].size(); i++) {
			ll v = adj[u][i].second;
			if (color[v] == BLACK) {
				continue;
			}
			if (d[v]>d[u] + adj[u][i].first) {
				d[v] = d[u] + adj[u][i].first;
				pq.push(make_pair(d[v], v));
				color[v] = GRAY;
			}
		}
	}
}


int main() {
	int n, m, k, s, t, i;
	cin >> n >> m >> k >> s >> t;
	s--; t--;
	vll floor(n);
	floor[0].push_back(s);
	floor[n - 1].push_back(t);
	mp[0][s] = cnt++;
	mp[n - 1][t] = cnt++;
	for (i = 0; i < m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		a--; b--; c--;
		if (mp[a][b] == 0) {
			mp[a][b] = cnt++;
			floor[a].push_back(b);
		}
		if (mp[a + 1][c] == 0) {
			mp[a + 1][c] = cnt++;
			floor[a + 1].push_back(c);
		}
		adj[mp[a][b]].push_back(pll(0, mp[a + 1][c]));
	}
	for (i = 0; i < n; i++) {
		sort(floor[i].begin(), floor[i].end());
		for (int j = 0; j + 1 < floor[i].size(); j++) {
			int a = floor[i][j];
			int b = floor[i][j + 1];
			if (a != b) {
				//cout << i << " " << a << " " << b << endl;
				ll u = mp[i][a], v = mp[i][b];
				//cout << i << " " << u << " " << v << endl;
				adj[u].push_back(pll(abs(b - a), v));
				adj[v].push_back(pll(abs(a - b), u));
			}
		}
	}
	/*
	for (i = 0; i < cnt; i++) {
	for (int j = 0; j < adj[i].size(); j++) {
	printf("(%d, %d, %d)  ", i, adj[i][j].first, adj[i][j].second);
	}
	cout << endl;
	}
	*/

	dijkstra();
	if (d[mp[n - 1][t]] == INF) {
		cout << -1 << endl;
	}
	else {
		cout << d[mp[n - 1][t]] << endl;
	}
}