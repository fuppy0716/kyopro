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

#define N 100005
vii q(N, vi());
vector<bool> used(N, false);
vi ans;

int main() {
	int n, m, i, j;
	cin >> n >> m;
	int a, b;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		a--; b--;
		q[a].push_back(b);
		q[b].push_back(a);
	}
	ans.push_back(a);
	ans.push_back(b);
	int left = ans[0], right = ans[1];
	used[ans[0]] = used[ans[1]] = true;
	vi head;
	while (true) {
		bool flag = true;
		for (i = 0; i < q[left].size(); i++) {
			if (!used[q[left][i]]) {
				flag = false;
				left = q[left][i];
				head.push_back(left);
				used[left] = true;
				break;
			}
		}
		if (flag) {
			break;
		}
	}
	reverse(head.begin(), head.end());
	vi tail;
	while (true) {
		bool flag = true;
		for (i = 0; i < q[right].size(); i++) {
			if (!used[q[right][i]]) {
				flag = false;
				right = q[right][i];
				tail.push_back(right);
				used[right] = true;
				break;
			}
		}
		if (flag) {
			break;
		}
	}
	cout << head.size() + 2 + tail.size() << endl;
	for (i = 0; i < head.size(); i++) {
		cout << head[i] + 1 << " ";
	}
	for (i = 0; i < ans.size(); i++) {
		cout << ans[i] + 1 << " ";
	}
	for (i = 0; i < tail.size(); i++) {
		cout << tail[i] + 1 << " ";
	}
	cout << endl;
}