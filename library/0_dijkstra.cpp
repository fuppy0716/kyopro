#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i,a,b) for(i=a;i<b;i++)
#define rloop(i,a,b) for(i=a;i>=b;i--)
#define vi vector<int>
#define vl vector<ll>
#define vii vector< vector<int> >
#define vll vector< vector<ll> >
#define vs vector<string>
const int inf=1000000001;
const ll INF=1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define pll pair<ll, ll>
static const int WHITE=0;
static const int GRAY=1;
static const int BLACK=2;
static const int N=10000;

int n;
vector< vector< pair<int,int> > > adj(N,vector< pair<int,int> >());
vl d(N,INF);

void dijkstra(int s);


vl dijkstra(int s, int n){
	priority_queue<pll, vector<pll>, greater<pll> > pq;
	int i;
	vl d(n, INF);
	d[s]=0;
	pq.push(make_pair(0,s));
	
	while(!pq.empty()){
		pll f=pq.top();
		pq.pop();
		int u=f.second;
		if(d[u]<f.first){
			continue;
		}
		for (i = 0; i < adj[u].size(); i++) {
			int v=adj[u][i].second;
			if (d[v] > d[u] + G[u][i].first) {
				d[v] = d[u] + G[u][i].first;
				pq.push(make_pair(d[v], v));
			}
		}
	}
	return d;
}
