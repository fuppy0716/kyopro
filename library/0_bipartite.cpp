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
#define pll pair<ll,ll>
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

#define N 100010
vii G(N, vi()); //�O���t�̗אڃ��X�g�\��
vi match(N); //�}�b�`���O�̃y�A
vector<bool> used(N); //DFS�ł��łɒ��ׂ����̃t���O
int n, m;
vi color(N, -1);

//�񕔃O���t���ǂ����𔻒f
bool bipartite() {
	stack<int> st;
	color[0] = 0;
	st.push(0);
	int i, j;
	while (!st.empty()) {
		i = st.top();
		st.pop();
		for (j = 0; j < G[i].size(); j++) {
			if (color[G[i][j]] == color[i]) {
				//cout << "NO" << endl;
				return false;
			}
			else {
				if (color[G[i][j]] == -1) {
					color[G[i][j]] = 1 - color[i];
					st.push(G[i][j]);
				}
			}
		}
	}
	//cout << "YES" << endl;
	return true;
}

//�}�b�`���O�Ɏg��
bool dfs(int v, vii &G, vi &match, vi &used) {
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    int u = G[v][i], w = match[u];
    if (w < 0 || !used[w] && dfs(w, G, match, used)) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

//�񕔃O���t�̍ő�}�b�`���O�����߂�
//�񕔃O���t�̍ő�}�b�`���O = �ŏ��_�J�o�[ = n-�ŏ��ӃJ�o�[ = n-�ő����W��
// http://buyoh.hateblo.jp/entry/2017/06/12/085722
// ���_�ɏd�݂����Ă�ŏ��_�J�o�[��url, Dinic�ŉ�����
int bipartite_matching(vii &G) {
  int res = 0;
  vi match(G.size(), -1);
  vi used(G.size());
  for (int v = 0; v < G.size(); v++) {
    if (match[v] < 0) {
      fill(used.begin(), used.end(), 0);
      if (dfs(v, G, match, used)) {
        res++;
      }
    }
  }
  return res;
}

int main() {
	int i, j;
	scanf("%lld%lld", &n, &m);
	int a, b;

	for (i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		a--; b--;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bool flag = bipartite();
	if (flag) {
		ll w = 0, b = 0;
		for (i = 0; i < n; i++) {
			if (color[i] == 0) {
				w++;
			}
			else {
				b++;
			}
		}
		cout << w*b - m << endl;
		return 0;
	}
	else {
		cout << (n*n - n) / 2 - m << endl;
		return 0;
	}
}








const int N = 100100;
const int M = 100100;
vector<vector<pll> > G(N + 1);
vl u(M + N), v(M + N), w(M + N);

int main() {
	int n, m;
	cin >> n >> m;
	rep1(i, n) {
		G[0].push_back(pll(i, 0));
		u[i - 1] = 0; v[i - 1] = i; w[i - 1] = 0;
	}
	rep(i, m) {
		cin >> u[i + n] >> v[i + n] >> w[i + n];
		w[i + n]++;
		G[u[i + n]].push_back(pll(v[i + n], w[i + n]));
	}
	vi idx(n + 1);
	vl dp(n + m, -1);
	rep(i, n) {
		dp[i] = 0;
	}
}
