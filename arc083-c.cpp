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

int main() {
	int a, b, c, d, e, f, i, j;
	cin >> a >> b >> c >> d >> e >> f;
	vector<bool> mizu(f + 1, false);
	mizu[0] = true;
	for (i = 0; i <= f; i += 100) {
		if (mizu[i]) {
			if (i + 100 * a <= f) {
				mizu[i + 100 * a] = true;
			}
			if (i + 100 * b <= f) {
				mizu[i + 100 * b] = true;
			}
		}
	}
	vector<bool> satou(f + 1, false);
	satou[0] = true;
	for (i = 0; i <= f; i++) {
		if (satou[i]) {
			if (i + c <= f) {
				satou[i + c] = true;
			}
			if (i + d <= f) {
				satou[i + d] = true;
			}
		}
	}
	//DEBUG_VEC(mizu);
	//DEBUG_VEC(satou);
	double M = -1;
	int max_mizu = 0, max_satou = 0;
	for (i = 0; i <= f; i += 100) {
		for (j = 0; j <= f; j++) {
			if (i + j > f) {
				break;
			}
			if (mizu[i] && satou[j]) {
				if (j <= e*i / 100) {
					if ((double)j / (i + j) > M) {
						M = (double)j / (i + j);
						max_mizu = i;
						max_satou = j;
					}
				}
				else {
					break;
				}
			}
		}
	}
	cout << max_mizu + max_satou << " " << max_satou << endl;
	return 0;
}