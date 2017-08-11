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
#define M12 365103863
#define M6 668655281

double F(int n) {
	double a = 0.81*(1 - pow(0.81, n)) / (1 - 0.81);
	double b = 0.9*(1 - pow(0.9, n)) / (1 - 0.9);
	return sqrt(a) / b;
}

double f(int n) {
	return (F(n) - 1 / sqrt(19)) * 1200 / (F(1) - 1 / sqrt(19));
}

double g(double x) {
	return pow(2, x / 800);
}

double g_inv(double x) {
	return 800 * log2(x);
}


int main() {
	int n, i, j;
	cin >> n;
	vector<double> r(n);
	for (i = 0; i < n; i++) {
		cin >> r[i];
	}
	double a = 0, b = 0;;
	for (i = 0; i < n; i++) {
		a += g(r[i])*pow(0.9, i);
		b += pow(0.9, i);
	}
	double R = g_inv(a / b) - f(n);
	cout << (int)R << endl;
	return 0;
}