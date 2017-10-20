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
static const int N = 1010;

int n;
//i”Ô–Ú‚©‚çadj[i].second”Ô–Ú‚Í‚Â‚È‚ª‚Á‚Ä‚¢‚ÄAd‚Ý‚Íadj[i].first
vector< vector< pair<double, int> > > adj(N, vector< pair<double, int> >());
vector<double> d(N, inf * 4.0);

void dijkstra() {
	priority_queue< pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > pq;
	int i;
	vi color(n + 2, WHITE);

	d[0] = 0;
	pq.push(make_pair(0, 0));
	color[0] = GRAY;

	while (!pq.empty()) {
		pair<double, int> f = pq.top();
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
	ll xs, ys, xt, yt;
	scanf("%lld%lld%lld%lld", &xs, &ys, &xt, &yt);
	int i, j;
	scanf("%d", &n);
	vl x(n + 2), y(n + 2), r(n + 2);
	x[0] = xs; y[0] = ys; r[0] = 0;
	x[1] = xt; y[1] = yt; r[1] = 0;
	for (i = 2; i < n + 2; i++) {
		scanf("%lld%lld%lld", &x[i], &y[i], &r[i]);
	}
	for (i = 0; i < n + 2; i++) {
		for (j = i + 1; j < n + 2; j++) {
			double d = sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
			d -= (r[i] + r[j]);
			if (d < 0) {
				d = 0;
			}
			adj[i].push_back(make_pair(d, j));
			adj[j].push_back(make_pair(d, i));
		}
	}

	dijkstra();
	Sp(d[1]);

}