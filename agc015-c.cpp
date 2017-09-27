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
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
#define T tuple<int,int,int>

int main() {
	int n, m, q, i, j, k;
	cin >> n >> m >> q;
	vector< vector<char> > s(n + 1, vector<char>(m + 1, '0'));
	loop(i, 1, n + 1) {
		loop(j, 1, m + 1) {
			cin >> s[i][j];
		}
	}
	vector< vector<T> > dp(n + 1, vector<T>(m + 1, make_tuple(0, 0, 0)));
	loop(i, 1, n + 1) {
		loop(j, 1, m + 1) {
			get<0>(dp[i][j]) = get<0>(dp[i - 1][j]) + get<0>(dp[i][j - 1]) - get<0>(dp[i - 1][j - 1]);
			get<1>(dp[i][j]) = get<1>(dp[i - 1][j]) + get<1>(dp[i][j - 1]) - get<1>(dp[i - 1][j - 1]);
			get<2>(dp[i][j]) = get<2>(dp[i - 1][j]) + get<2>(dp[i][j - 1]) - get<2>(dp[i - 1][j - 1]);
			if (s[i][j] == '1') {
				get<0>(dp[i][j])++;
				if (s[i - 1][j] == '1') {
					get<1>(dp[i][j])++;
				}
				if (s[i][j - 1] == '1') {
					get<2>(dp[i][j])++;
				}
			}
		}
	}
	loop(i, 0, q) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int a, b, c;
		a = get<0>(dp[x2][y2]) - get<0>(dp[x1 - 1][y2]) - get<0>(dp[x2][y1 - 1]) + get<0>(dp[x1 - 1][y1 - 1]);
		b = get<1>(dp[x2][y2]) - get<1>(dp[x1][y2]) - get<1>(dp[x2][y1 - 1]) + get<1>(dp[x1][y1 - 1]);
		c = get<2>(dp[x2][y2]) - get<2>(dp[x1 - 1][y2]) - get<2>(dp[x2][y1]) + get<2>(dp[x1 - 1][y1]);
		cout << a - b - c << endl;
	}
}