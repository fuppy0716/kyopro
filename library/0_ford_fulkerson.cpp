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

// 辺を表す構造体 {行先、容量、逆辺}
struct edge { int to; ll cap; int rev; };
#define V 1010
int s, t; //sがstart, tがgoal
vector< vector<edge> > G(V, vector<edge>());; //グラフの隣接リスト表現
vector<bool> used(V); //DEFで調べたかのフラグ

					  //fromからtoへ向かう容量capの辺をグラフに追加する
void add_edge(int from, int to, ll cap) {
	edge a;
	a.to = to; a.cap = cap; a.rev = G[to].size();
	G[from].push_back(a);
	a.to = from; a.cap = 0; a.rev = G[from].size() - 1;
	G[to].push_back(a);
}

ll dfs(int v, int t, ll f) {
	if (v == t) {
		return f;
	}
	used[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		edge &e = G[v][i];
		if (!used[e.to] && e.cap > 0) {
			ll d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

ll max_flow(int s, int t) {
	ll flow = 0;
	while (true) {
		fill(used.begin(), used.end(), false);
		ll f = dfs(s, t, INF);
		if (f == 0) return flow;
		flow += f;
	}
}

int main() {
	int n, m, i;
	cin >> n >> m;
	for (i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		add_edge(a, b, c);
	}
	cout << max_flow(0, 4) << endl;
}

/*
4 7
0 1 10
0 2 2
1 2 6
1 3 6
2 4 5
3 2 3
3 4 8
*/