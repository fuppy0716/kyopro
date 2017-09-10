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
    static const int WHITE = 0;
    static const int GRAY = 1;
    static const int BLACK = 2;
    static const int N = 300;
     
    int n,R;
    vector< vector< pair<int, int> > > adj(N, vector< pair<int, int> >());
    vll hyou(8, vl(8, 0));
    vl d(N, INF);
    vi r(8);
     
    void dijkstra(int i) {
    	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
    	vi color(n + 1, WHITE);
     
    	d[r[i]-1] = 0;
    	pq.push(make_pair(0, r[i]-1));
    	color[r[i]-1] = GRAY;
     
    	while (!pq.empty()) {
    		pair<int, int> f = pq.top();
    		pq.pop();
    		int u = f.second;
    		color[u] = BLACK;
    		if (d[u] < f.first) {
    			continue;
    		}
    		for (int j = 0; j < adj[u].size(); j++) {
    			int v = adj[u][j].second;
    			if (color[v] == BLACK) {
    				continue;
    			}
    			if (d[v] > d[u] + adj[u][j].first) {
    				d[v] = d[u] + adj[u][j].first;
    				pq.push(make_pair(d[v], v));
    				color[v] = GRAY;
    			}
    		}
    	}
    	for (int j = 0; j < R; j++) {
    		hyou[i][j] = d[r[j]-1];
    	}
     
    }
     
     
    int main() {
    	srand((unsigned)time(NULL));
    	int m, i, j;
    	cin >> n >> m >> R;
    	for (i = 0; i < R; i++) {
    		cin >> r[i];
    	}
    	int a, b, c;
    	for (i = 0; i < m; i++) {
    		cin >> a >> b >> c;
    		adj[a-1].push_back(make_pair(c, b-1));
    		adj[b-1].push_back(make_pair(c, a-1));
    	}
    	for (i = 0; i < R; i++) {
    		for (j = 0; j < d.size(); j++) {
    			d[j] = INF;
    		}
    		dijkstra(i);
    	}
    	ll mini = INF;
    	vi jun(R);
    	for (i = 0; i < R; i++) {
    		jun[i] = i;
    	}
    	do {
    		ll sum = 0;
    		for (i = 1; i < R; i++) {
    			sum += hyou[jun[i - 1]][jun[i]];
    		}
    		mini = min(sum, mini);
    	} while (next_permutation(jun.begin(), jun.end()));
    	cout << mini << endl;
    }