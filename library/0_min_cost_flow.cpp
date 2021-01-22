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




// http://sigma425.hatenablog.com/entry/2014/10/12/122018
struct edge {int to,cap,cost,rev;};
const int MAX_V=6100;
int V;			//代入!!
vector<edge> G[MAX_V];
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];
int top[MAX_V];
void add_edge(int from, int to, int cap, int cost){
//	printf("%d->%d  cap=%d,cost=%d\n",from,to,cap,cost);
	edge e1={to,cap,cost,(int)G[to].size()},e2={from,0,-cost,(int)G[from].size()};
	G[from].push_back(e1);
	G[to].push_back(e2);
}

int min_cost_flow(int s, int t, int f){
    using P = pair<int, int>;
	int res=0;
	fill(h,h+V,0);
	rep(i,V){
		int v=top[i];
		rep(j,G[v].size()){
			edge &e=G[v][j];
			if(e.cap==0) continue;
			int u=e.to;
			h[u]=min(h[u],h[v]+e.cost);
		}
	}
	while(f>0){
		priority_queue< P,vector<P>,greater<P> > que;
		fill(dist,dist+V,inf);
		dist[s]=0;
		que.push(P(0,s));
		while(!que.empty()){
			P p=que.top();
			que.pop();
			int v=p.second;
			if(dist[v]<p.first) continue;
			for(int i=0;i<G[v].size();i++){
				edge &e=G[v][i];
				if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
					dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
					prevv[e.to]=v;
					preve[e.to]=i;
					que.push(P(dist[e.to],e.to));
				}
			}
		}
		if(dist[t]==inf) return -1;
		for(int v=0;v<V;v++) h[v]+=dist[v];
		int d=f;
		for(int v=t;v!=s;v=prevv[v]){
			d=min(d,G[prevv[v]][preve[v]].cap);
		}
		f-=d;
		res+=d*h[t];
		for(int v=t;v!=s;v=prevv[v]){
			edge &e=G[prevv[v]][preve[v]];
			e.cap-=d;
			G[v][e.rev].cap+=d;
		}
	}
	return res;
}