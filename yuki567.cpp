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

int main() {
	int n, i, j;
	cin >> n;
	vi C = { 1, 6, 15, 20, 15, 6, 1 };
	double ans = 1;
	int fugou = -1;
	for (i = 5; i >= 1; i--) {
		ans += fugou * pow((double)i / 6, n) * C[6 - i];
		fugou *= -1;
	}
	Sp(ans);
}