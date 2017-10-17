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

static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;
#define N 100010
#define M 200010
vector< vector<pii> > adj(4 * M, vector<pii>());
int cnt = 0;
int n, m;
map<pii, int> mp;
vector< set<int> > station(4 * M);
vi d(4 * M, inf);

int get_id(int p, int c) {
	pii pr = make_pair(p, c);
	if (mp[pr]) {
		//cout << mp[pr] << endl;
		return mp[pr];
	}
	else {
		mp[pr] = ++cnt;
		//cout << mp[pr] << endl;
		return mp[pr];
	}
}

void dijkstra(int s) {
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
	int i;
	vi color(4 * M, WHITE);

	d[s] = 0;
	pq.push(make_pair(0, s));
	color[s] = GRAY;

	while (!pq.empty()) {
		pair<int, int> f = pq.top();
		pq.pop();
		int u = f.second;
		color[u] = BLACK;
		if (d[u]<f.first) {
			continue;
		}
		for (i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].second;
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
	int i, j;
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; i++) {
		int p, q, c;
		scanf("%d%d%d", &p, &q, &c);
		p--; q--;
		int u = get_id(p, c), v = get_id(q, c);
		adj[u].push_back(make_pair(0, v));
		adj[v].push_back(make_pair(0, u));
		station[p].insert(c);
		station[q].insert(c);
	}
	for (i = 0; i < n; i++) {
		for (auto itr = station[i].begin(); itr != station[i].end(); itr++) {
			int u = get_id(i, *itr);
			int v = get_id(i, -1);
			adj[u].push_back(make_pair(0, v));
			adj[v].push_back(make_pair(1, u));
		}
	}
	int s = get_id(0, -1), g = get_id(n - 1, -1);
	dijkstra(s);
	if (d[g] == inf) {
		printf("-1\n");
		return 0;
	}
	else {
		printf("%d\n", d[g]);
		return 0;
	}
}