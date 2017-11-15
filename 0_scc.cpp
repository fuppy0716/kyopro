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

//scc : strongly connected component

int n; //頂点数
#define N 10010
vii G(N, vi()); //グラフの隣接リスト表現
vii rG(N, vi()); //辺の向きを逆にしたグラフ
vi vr; //帰りがけ順のならび
vector<bool> used(N); //すでに調べたか
vi cmp(N); //属する強連結成分のトポロジカル順序

void add_edge(int from, int to) {
	G[from].push_back(to);
	rG[to].push_back(from);
}

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		if (!used[G[v][i]]) {
			dfs(G[v][i]);
		}
	}
	vr.push_back(v);
}

void rdfs(int v, int k) {
	used[v] = true;
	cmp[v] = k;
	for (int i = 0; i < rG[v].size(); i++) {
		if (!used[rG[v][i]]) {
			rdfs(rG[v][i], k);
		}
	}
}


int scc() {
	fill(used.begin(), used.end(), false);
	vr.clear();
	for (int v = 0; v < n; v++) {
		if (!used[v]) dfs(v);
	}
	fill(used.begin(), used.end(), false);
	int k = 0;
	for (int i = vr.size() - 1; i >= 0; i--) {
		if (!used[vr[i]]) rdfs(vr[i], k++);
	}
	return k;
}

int main() {
	int m, i, j;
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		add_edge(a, b);
	}
	int l = scc();

	int u = 0, num = 0;
	for (int v = 0; v < n; v++) {
		if (cmp[v] == l - 1) {
			u = v;
			num++;
		}
	}
	fill(used.begin(), used.end(), false);
	rdfs(u, 0);
	for (int v = 0; v < n; v++) {
		if (!used[v]) {
			num = 0;
			break;
		}
	}
	printf("%d\n", num);
}
