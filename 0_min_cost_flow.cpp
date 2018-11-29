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

#define MAX_V 1000

struct edge { int to, cap, cost, rev; };
int V; //���_��
vector< vector<edge> > G(MAX_V); //�O���t�̗אڃ��X�g�\��
vi h(MAX_V); //�|�e���V����
vi dist(MAX_V); //�ŒZ����
vi prevv(MAX_V), preve(MAX_V); //���O�̒��_�ƕ�

							   //from����to�֌������e��cap,�R�X�gcost�̕ӂ��O���t�ɒǉ�����
void add_edge(int from, int to, int cap, int cost) {
	edge temp;
	temp.to = to; temp.cap = cap; temp.cost = cost; temp.rev = G[to].size();
	G[from].push_back(temp);
	temp.to = from; temp.cap = 0; temp.cost = -cost; temp.rev = G[from].size() - 1;
	G[to].push_back(temp);
}

//s����t�ւ̗���f�̍ŏ���p�������߂�
//�����Ȃ��ꍇ��-1��Ԃ�
int min_cost_flow(int s, int t, int f) {
	int res = 0;
	fill(h.begin(), h.end(), 0);
	while (f > 0) {
		priority_queue<pii, vector<pii>, greater<pii> > que; //first�͍ŒZ�����Asecond�͒��_�̔ԍ�
		fill(dist.begin(), dist.end(), inf);
		dist[s] = 0;
		que.push(pii(0, s));
		while (!que.empty()) {
			pii p = que.top(); que.pop();
			int v = p.second;
			if (dist[v] < p.first) continue;
			for (int i = 0; i < G[v].size(); i++) {
				edge &e = G[v][i];
				if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
					dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(pii(dist[e.to], e.to));
				}
			}
		}
		if (dist[t] == inf) { //����ȏ㗬���Ȃ�
			return -1;
		}
		for (int v = 0; v < V; v++) {
			h[v] += dist[v];
		}
		int d = f;
		for (int v = t; v != s; v = prevv[v]) {
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d*h[t];
		for (int v = t; v != s; v = prevv[v]) {
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}
