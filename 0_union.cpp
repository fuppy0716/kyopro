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
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
const int inf=1000000001;
const ll INF=1e18;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4]={1,0,-1,0}, dy[4]={0,1,0,-1};



class UnionFind {
public:
	int n;
	vi par; //親
	vi ran; //木の深さ
	vi num; //要素数

	UnionFind(int _n) {
		n = _n;
		par.resize(n); ran.resize(n); num.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i; ran[i] = 0; num[i] = 1;
		}
	}

	//木の根を求める
	int find(int x) {
		if (par[x] == x) {
			return x;
		}
		else {
			return par[x] = find(par[x]);
		}
	}

	//xとyの属する集合を併合
	void unite(int x, int y) {
		x = find(x); y = find(y);
		int numsum = num[x] + num[y];
		if (x == y) {
			return;
		}
		if (ran[x]<ran[y]) {
			par[x] = y;
		}
		else {
			par[y] = x;
			if (ran[x] == ran[y]) {
				ran[x]++;
			}
		}
		num[x] = num[y] = numsum;
	}

	//xとyが同じ集合に属するか否か
	bool same(int x, int y) {
		return find(x) == find(y);
	}

};

//部分永続UF
class PermanenceUF {
public:
	int n;
	vi par; //親
	vi ran; //木の深さ
	vector<vector<pll> > num; //要素数
	vl time; //木が更新された時の時刻

	PermanenceUF(int _n) {
		n = _n;
		par.resize(n); ran.resize(n);
		num.resize(n); time.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i; ran[i] = 0; time[i] = INF;
			num[i] = vector<pll>(1, pii(0, 1));
		}
	}

	//時刻tの時の木の根を求める
	int find(ll t, int x) {
		if (time[x] > t) return x;
		else return find(t, par[x]);
	}

	//時刻tにxとyの属する集合を併合
	//tは単調増加している
	void unite(ll t, int x, int y) {
		x = find(t, x); y = find(t, y);
		ll numsum = num[x].back().second + num[y].back().second;
		if (x == y) {
			return;
		}
		if (ran[x] < ran[y]) {
			swap(x, y);
		}
		par[y] = x;
		time[y] = t;
		num[x].push_back(pll(t, numsum));
		if (ran[x] == ran[y]) {
			ran[x]++;
		}
	}

	//時刻t1のxとt2のyが同じ集合に属するか否か
	bool same(ll t1, int x, ll t2, int y) {
		return find(t1, x) == find(t2, y);
	}

	//時刻tの時の要素xを含む集合のサイズ
	int size(ll t, int x) {
		int root = find(t, x);
		int left = 0, right = num[root].size();
		while (left + 1 < right) {
			int mid = (left + right) / 2;
			if (num[root][mid].first <= t) {
				left = mid;
			}
			else {
				right = mid;
			}
		}
		return num[root][left].second;
	}

};


int main(){
	int n,k,i;
	cin>>n>>k;
	loop(i,0,k){
		cin>>T[i]>>X[i]>>Y[i];
	}
	init(n*3);
	int ans=0;
	loop(i,0,k){
		int t=T[i];
		int x=X[i]-1,y=Y[i]-1;
		
		if(x<0 || x>=n || y<0 || y>=n){
			ans++;
			continue;
		}
		
		if(t==1){
			if(same(x,y+n) || same(x,y+2*n)){
				ans++;
			}
			else{
				unite(x,y);
				unite(x+n,y+n);
				unite(x+2*n,y+2*n);
			}
		}else{
			if(same(x,y) || same(x,y+2*n)){
				ans++;
			}else{
				unite(x,y+n);
				unite(x+n,y+2*n);
				unite(x+2*n,y);
			}
		}
	}
	cout<<ans<<endl;
}





#define N 100010
#define M 200010
int n, m;
vl l(M), r(M), d(M);
vl x(N, -INF);
vector<vector<pii> > G(N, vector<pii>());
vector<bool> used(N, false);
queue<int> nexta;
ll minx = INF, maxx = -INF;

void dfs(int u) {
	int nowx = x[u];
	for (int i = 0; i < G[u].size(); i++) {
		if (!used[G[u][i].first]) {
			nexta.push(G[u][i].first);
			if (x[G[u][i].first] == -INF) {
				x[G[u][i].first] = nowx + G[u][i].second;
				minx = min(minx, x[G[u][i].first]);
				maxx = max(maxx, x[G[u][i].first]);
			}
			else {
				if (x[G[u][i].first] != nowx + G[u][i].second) {
					cout << "No" << endl;
					exit(0);
				}
			}
		}
	}
	while (!nexta.empty()) {
		int v = nexta.front();
		nexta.pop();
		if (!used[v]) {
			dfs(v);
		}
	}
}

int main() {
	cin >> n >> m;

	int i, j;
	map<int, int> mp;
	int cnt = 1;
	vector<vector<pair<pii, int> > > a;
	for (i = 0; i < m; i++) {
		cin >> l[i] >> r[i] >> d[i];
		l[i]--; r[i]--;
		G[l[i]].push_back(pii(r[i], d[i]));
		G[r[i]].push_back(pii(l[i], -d[i]));
	}
	for (i = 0; i < n; i++) {
		if (used[i]) {
			continue;
		}
		dfs(i);
		if (maxx - minx > 1000000000) {
			cout << "No" << endl;
			return 0;
		}
		minx = INF; maxx = -INF;
	}
	cout << "Yes" << endl;
}

/*
int main() {
int n, m;
cin >> n >> m;

init(n);
int i, j;
vl l(m), r(m), d(m);
map<int, int> mp;
int cnt = 1;
vector<vector<pair<pii, int> > > a;
for (i = 0; i < m; i++) {
cin >> l[i] >> r[i] >> d[i];
l[i]--; r[i]--;
if (l[i] > r[i]) {
swap(l[i], r[i]);
d[i] *= -1;
}
unite(l[i], r[i]);
}
for (i = 0; i < m; i++) {
int temp = mp[find(l[i])];
if (temp == 0) {
mp[find(l[i])] = cnt++;
a.push_back(vector<pair<pii, int> >());
a[cnt - 2].push_back(make_pair(pii(l[i], r[i]), d[i]));
}
else {
a[temp - 1].push_back(make_pair(pii(l[i], r[i]), d[i]));
}
}
vl x(n, -INF);
for (i = 0; i < a.size(); i++) {
sort(a.begin(), a.end());
}
for (i = 0; i < a.size(); i++) {
x[a[i][0].first.first] = 0;
x[a[i][0].first.second] = a[i][0].second;
for (j = 1; j < a[i].size(); j++) {

}
}
}
*/
