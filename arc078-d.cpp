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
static const int RED = 3;
static const int BLACK2 = 10;
static const int WHITE2 = 8;

static const int N = 100010;

//ttŽžAd[v]v‚ðÅ‰‚É”­Œ©‚µ‚½ŽžAf[v]v‚ð’²‚×I‚í‚Á‚½Žž
int n, tt = 0;
vii M(N, vi());
vi color(N, RED), d(N), f(N), nt(N, 0);

void dfs(int);
int next(int);

void bfs(int r, int c);



void dfs(int r) {
	stack<int> s;
	s.push(r);
	color[r] = GRAY;
	d[r] = ++tt;

	while (!s.empty()) {
		int u = s.top();
		int v = next(u);
		if (v != -1) {
			if (color[v] == RED) {
				color[v] = GRAY;
				d[v] = ++tt;
				s.push(v);
			}
		}
		else {
			s.pop();
			color[u] = BLACK;
			f[u] = ++tt;
		}
	}
}

int next(int u) {
	int i;
	for (i = 0; i < M[u].size(); i++) {
		if (color[M[u][i]] == RED) {
			return M[u][i];
		}
	}
	return -1;
}


void bfs(int r, int c) {
	queue<int> q;
	int i;
	q.push(r);
	while (!q.empty()) {
		int u = q.front();
		for (i = 0; i < M[u].size(); i++) {
			if (color[M[u][i]] == RED || color[M[u][i]] == c) {
				q.push(M[u][i]);
				color[M[u][i]] = GRAY;
			}
		}
		color[u] = c + 8;
		q.pop();
	}
}


int main() {
	cin >> n;
	int i;
	for (i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		M[a - 1].push_back(b - 1);
		M[b - 1].push_back(a - 1);
	}
	dfs(0);
	int tw = d[n - 1];
	int now = n - 1;
	vi keiro;
	while (1 < tw) {
		for (i = 0; i < M[now].size(); i++) {
			if (d[M[now][i]] < tw) {
				keiro.push_back(now);
				tw = d[M[now][i]];
				now = M[now][i];
			}
		}
	}


	for (i = 0; i < n; i++) {
		color[i] = RED;
	}
	color[0] = BLACK;
	color[n - 1] = WHITE;
	int right = keiro.size() - 1;
	int left = 1;
	while (left<right) {
		if (color[keiro[right]] == RED) {
			color[keiro[right]] = BLACK;
			right--;
		}
		if (color[keiro[left]] == RED) {
			color[keiro[left]] = WHITE;
			left++;
		}
	}
	bfs(0, BLACK);
	bfs(n - 1, WHITE);
	int b = 0, w = 0;
	for (i = 0; i < n; i++) {
		if (color[i] == BLACK2) {
			b++;
		}
		else {
			w++;
		}
	}
	if (b > w) {
		cout << "Fennec" << endl;
	}
	else {
		cout << "Snuke" << endl;
	}
}