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

int main() {
	int h, w;
	cin >> h >> w;
	int n;
	cin >> n;
	int i, j;
	vi a(n);
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	vi c(h*w);
	int k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < a[i]; j++) {
			c[k] = i + 1;
			k++;
		}
	}
	bool flag = true;
	for (i = 0; i < h; i++) {
		if (flag) {
			for (j = 0; j < w; j++) {
				cout << c[i*w + j] << " ";
			}
		}
		else {
			for (j = w - 1; j >= 0; j--) {
				cout << c[i*w + j] << " ";
			}
		}
		cout << endl;
		flag = !flag;
	}
}