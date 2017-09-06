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
static const int WHITE=0;
static const int GRAY=1;
static const int BLACK=2;
static const int N=10000;

int n;
vector< vector< pair<int,int> > > adj(N,vector< pair<int,int> >());
vi d(N,inf);

void dijkstra();

int main(){
	int k,u,v,c,i,j;
	cin>>n;
	loop(i,0,n){
		cin>>u>>k;
		loop(j,0,k){
			cin>>v>>c;
			adj[u].push_back(make_pair(c,v));
		}
	}
	dijkstra();
	loop(i,0,n){
		cout<<i<<" "<<((d[i]==inf)? -1:d[i])<<endl;
	}
}

void dijkstra(){
	priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > pq;
	int i;
	vi color(n,WHITE);
	
	d[0]=0;
	pq.push(make_pair(0,0));
	color[0]=GRAY;
	
	while(!pq.empty()){
		pair<int,int> f=pq.top();
		pq.pop();
		int u=f.second;
		color[u]=BLACK;
		if(d[u]<f.first){
			continue;
		}
		loop(i,0,adj[u].size()){
			int v=adj[u][i].second;
			if(color[v]==BLACK){
				continue;
			}
			if(d[v]>d[u]+adj[u][i].first){
				d[v]=d[u]+adj[u][i].first;
				pq.push(make_pair(d[v],v));
				color[v]=GRAY;
			}
		}
	}
}
	