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

#define N 1010
#define M 2010
struct edge { ll from, to, cost; };
vector<edge> es(M);

vl d(N,INF);
ll n, m;

//trueを返す場合、頂点以上に更新チェック→負のコストの閉ループあり
bool bellman_ford(ll s) {
	d[s] = 0;
	ll cnt = 0;
	bool updateFlag;
	while (true) {
		updateFlag = false;
		for (i = 0; i < m; i++) {
			if (d[es[i].from] != INF && d[es[i].to] > d[es[i].from] + es[i].cost) {
				d[es[i].to] = d[es[i].from] + es[i].cost;
				updateFlag = true;
			}
		}

		if (cnt == n - 1) return true;
		if (!updateFlag) break;

		cnt += 1;
	}
	return false;
}