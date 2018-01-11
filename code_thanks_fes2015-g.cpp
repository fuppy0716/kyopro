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
static const int N = 160050;

int n;
//i”Ô–Ú‚©‚çadj[i].second”Ô–Ú‚Í‚Â‚È‚ª‚Á‚Ä‚¢‚ÄAd‚Ý‚Íadj[i].first
vector< vector< pair<ll, int> > > adj(N, vector< pair<ll, int> >());
vl d(N, INF);
#define pli pair<ll, int> 


void dijkstra() {
	priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > pq;
	int i;
	vi color(n, WHITE);

	d[0] = 0;
	pq.push(make_pair(0, 0));
	color[0] = GRAY;

	while (!pq.empty()) {
		pair<ll, int> f = pq.top();
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


signed main() {
	int n0, m, i, j, k;
	scanf("%d%d", &n0, &m);
	vii index(n0);
	vi a(m), b(m), c(m), t(m);
	n = 2 * m + 2;
	for (i = 0; i < m; i++) {
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &t[i]);
		a[i]--; b[i]--;
		index[a[i]].push_back(i);
		index[b[i]].push_back(i);
		int u = i * 2 + 1, v = i * 2 + 2;
		adj[u].push_back(pli((ll)t[i], v));
		adj[v].push_back(pli((ll)t[i], u));
	}
	for (i = 0; i < n0; i++) {
		vector<pli> col(index[i].size());
		for (j = 0; j < index[i].size(); j++) {
			int idx = index[i][j];
			int u;
			if (a[idx] == i) {
				u = idx * 2 + 1;
			}
			else {
				u = idx * 2 + 2;
			}
			col[j] = pli(c[idx], u);
		}
		sort(col.begin(), col.end());
		for (j = 0; j < index[i].size() - 1; j++) {
			int u = col[j].second;
			int v = col[j + 1].second;
			adj[u].push_back(pli(abs(col[j].first - col[j + 1].first), v));
			adj[v].push_back(pli(abs(col[j].first - col[j + 1].first), u));

		}
	}
	for (i = 0; i < index[0].size(); i++) {
		int idx = index[0][i];
		int u;
		if (a[idx] == 0) {
			u = idx * 2 + 1;
		}
		else {
			u = idx * 2 + 2;
		}
		adj[0].push_back(pli((ll)c[idx] - 1, u));
		adj[u].push_back(pli((ll)c[idx] - 1, 0));
	}
	for (i = 0; i < index[n0 - 1].size(); i++) {
		int idx = index[n0 - 1][i];
		int u;
		if (a[idx] == n0 - 1) {
			u = idx * 2 + 1;
		}
		else {
			u = idx * 2 + 2;
		}
		adj[u].push_back(pli(0, n - 1));
		adj[n - 1].push_back(pli(0, u));
	}

	/*
	for (i = 0; i < n0; i++) {
	cout << i << endl;
	for (j = 0; j < index[i].size(); j++) {
	cout << index[i][j] << " ";
	}
	cout << endl;
	}
	cout << endl;
	for (i = 0; i < n; i++) {
	cout << i << endl;
	for (j = 0; j < adj[i].size(); j++) {
	cout << adj[i][j].second << " " << adj[i][j].first << endl;
	}
	}
	*/

	dijkstra();
	cout << d[n - 1] << endl;
}
