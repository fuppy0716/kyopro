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

const ll MAX_N = 1 << 17;
ll n;
vl dat(2 * MAX_N - 1);

void init(ll n_) {
	n = 1;
	//簡単のため、要素数nを2のべき乗にする
	while (n < n_) n *= 2;
	for (int i = 0; i < 2 * n - 1; i++) {
		dat[i] = INF;
	}
}

//k番目の値をaに変更
void update(int k, int a) {
	k += n - 1;
	dat[k] = a;
	while (k > 0) {
		k = (k - 1) / 2;
		dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
	}
}

//[a,b)の最小値を求める
//後ろのほうの引数は計算の簡単のための引数
//kは接点の番号,l,rはその接点が[l,r)に対応していることを表す
//従って、外からはquery(a,b,0,0,n)としてよぶ
int query(int a, int b, int k, int l, int r) {
	if (r <= a || b <= l) {
		return INF;
	}
	if (a <= l && r <= b) {
		return dat[k];
	}
	else {
		ll ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
		ll ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return min(ul, ur);
	}
}

int main() {
	init(8);
	update(0, 5);
	update(1, 3);
	update(2, 7);
	update(3, 9);
	update(4, 6);
	update(5, 4);
	update(6, 1);
	update(7, 2);

	cout << query(2, 7, 0, 0, n) << endl;
}