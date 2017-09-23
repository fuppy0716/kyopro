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
static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;
static const int N = 100010;

int n;
//i”Ô–Ú‚©‚çadj[i].second”Ô–Ú‚Í‚Â‚È‚ª‚Á‚Ä‚¢‚ÄAd‚Ý‚Íadj[i].first
vector< vector< pair<int, int> > > adj(N, vector< pair<int, int> >());
vl d(N, INF);

void dijkstra(int s) {
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
	int i;
	vi color(n, WHITE);

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
	cin >> n;
	for (i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		adj[a].push_back(make_pair(c, b));
		adj[b].push_back(make_pair(c, a));
	}
	int q, k;
	cin >> q >> k;
	k--;
	dijkstra(k);
	for (i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		cout << d[x] + d[y] << endl;
	}

}