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
#define pll pair<ll,ll>
const int inf = 1000000001;
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int ask(int x, int y, int z) {
	int d;
	cout << "?" << " " << x << " " << y << " " << z << endl;
	cin >> d;
	return d;
}

void answer(int x, int y, int z) {
	cout << "!" << " " << x << " " << y << " " << z << endl;
}


int main() {
	int i, j;
	int haba = 100;
	int x = 0, y = 0, z = 0;
	while (haba > 0) {
		int zu = z + haba, zd = z - haba;
		int d, du, dd;
		d = ask(x, y, z);
		du = ask(x, y, zu);
		dd = ask(x, y, zd);
		if (du <= d && du <= dd) {
			z = zu;
		}
		else if (dd <= du && dd <= d) {
			z = zd;
		}
		if (haba == 1)
			break;
		haba = (haba + 1) / 2;
	}
	haba = 100;
	while (haba > 0) {
		int yu = y + haba, yd = y - haba;
		int d, du, dd;

		d = ask(x, y, z);
		du = ask(x, yu, z);
		dd = ask(x, yd, z);
		if (du <= d && du <= dd) {
			y = yu;
		}
		else if (dd <= du && dd <= d) {
			y = yd;
		}
		if (haba == 1)
			break;
		haba = (haba + 1) / 2;
	}
	haba = 100;
	while (haba > 0) {
		int xu = x + haba, xd = x - haba;
		int d, du, dd;

		d = ask(x, y, z);
		du = ask(xu, y, z);
		dd = ask(xd, y, z);
		if (du <= d && du <= dd) {
			x = xu;
		}
		else if (dd <= du && dd <= d) {
			x = xd;
		}
		if (haba == 1)
			break;
		haba = (haba + 1) / 2;
	}
	answer(x, y, z);
	return 0;


}