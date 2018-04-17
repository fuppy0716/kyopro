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

#define ci complex<ll>
//x,yの順に辞書順ソート
bool cmp_x(const ci p, const ci q) {
	if (p.real() != q.real()) return p.real() < q.real();
	return p.imag() < q.imag();
}

//位置ベクトルa,bの外積
ll det(ci a, ci b) {
	return a.real()*b.imag() - b.real()*a.imag();
}

//位置ベクトルa,bの内積
ll dot(ci a, ci b) {
	return a.real()*b.real() + a.imag()*b.imag();
}

//ps: 全部の座標, n: 座標数。凸包の集合を返す
vector<ci> convex_hull(vector<ci> ps, int n) {
	sort(ps.begin(), ps.end(), cmp_x);
	int k = 0; //凸包の頂点数
	vector<ci> qs(n * 2); //構築中の凸包
	for (int i = 0; i < n; i++) {
		while (k > 1 && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	for (int i = n - 2, t = k; i >= 0; i--) {
		while (k > t && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k - 1);
	return qs;
}

int main() {
	int n, i, j;
	cin >> n;
	vector<ci> ps(n);
	for (i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		ps[i].real(x); ps[i].imag(y);
	}

	vector<vector<char> > s2(10, vector<char>(10, '.'));
	for (i = 0; i < n; i++) {
		s2[ps[i].imag()][ps[i].real()] = '#';
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			cout << s2[i][j];
		}
		cout << endl;
	}
	cout << endl;
	ps = convex_hull(ps, n);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			s2[i][j] = '.';
		}
	}
	for (i = 0; i < ps.size(); i++) {
		s2[ps[i].imag()][ps[i].real()] = '#';
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			cout << s2[i][j];
		}
		cout << endl;
	}
}
/*
8
0 5 1 8 3 4 5 0 6 2 6 6 8 3 8 7
*/