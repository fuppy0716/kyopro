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
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


class SegmentTree {
public:
	const ll MAX_N = 1 << 20;
	int n;
	vector<pii> dat;
	vector<pii> a;

	SegmentTree(int _n, vector<pii> _a) :n(_n), a(_a) { dat.resize(2 * MAX_N - 1); }
	SegmentTree() { dat.resize(2 * MAX_N - 1); }

	void init(int k, int l, int r) {
		if (r - l == 1) {
			dat[k] = a[l];
		}
		else {
			int lch = 2 * k + 1, rch = 2 * k + 2;
			init(lch, l, (l + r) / 2);
			init(rch, (l + r) / 2, r);
			dat[k] = min(dat[lch], dat[rch]);
		}
	}



	//[a,b)の最小値を求める
	//後ろのほうの引数は計算の簡単のための引数
	//kは接点の番号,l,rはその接点が[l,r)に対応していることを表す
	//従って、外からはquery(a,b,0,0,n)としてよぶ
	pii query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) {
			return pii(inf, -1);
		}
		if (a <= l && r <= b) {
			return dat[k];
		}
		else {
			pii ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
			pii ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(ul, ur);
		}
	}

};


SegmentTree steven;
SegmentTree stodd;

class Cmp {
public:
	bool operator() (pii a, pii b) {
		int amin, bmin;
		if (a.first % 2 == 0) {
			amin = steven.query(a.first / 2, a.second / 2, 0, 0, steven.n).first;
		}
		else {
			amin = stodd.query(a.first / 2, a.second / 2, 0, 0, stodd.n).first;
		}

		if (b.first % 2 == 0) {
			bmin = steven.query(b.first / 2, b.second / 2, 0, 0, steven.n).first;
		}
		else {
			bmin = stodd.query(b.first / 2, b.second / 2, 0, 0, stodd.n).first;
		}

		if (amin < bmin) {
			return false;
		}
		else {
			return true;
		}
	}
};


int main() {
	int i, j;
	int n;
	cin >> n;
	vector<pii> podd(n / 2), peven(n / 2);
	for (i = 0; i < n / 2; i++) {
		cin >> peven[i].first >> podd[i].first;
		peven[i].second = 2 * i;
		podd[i].second = 2 * i + 1;
	}
	steven.n = n / 2;
	steven.a = peven;
	stodd.n = n / 2;
	stodd.a = podd;
	stodd.init(0, 0, n / 2);
	steven.init(0, 0, n / 2);

	priority_queue<pii, vector<pii>, Cmp> pq;
	pq.push(pii(0, n));
	vi q;
	for (int aaa = 0; aaa < n / 2; aaa++) {
		pii kukan = pq.top();
		pq.pop();
		pii m, aikata;
		if (kukan.first % 2 == 0) {
			m = steven.query(kukan.first / 2, kukan.second / 2, 0, 0, steven.n);
			aikata = stodd.query(m.second / 2, kukan.second / 2, 0, 0, stodd.n);
		}
		else {
			m = stodd.query(kukan.first / 2, kukan.second / 2, 0, 0, stodd.n);
			aikata = steven.query(m.second / 2 + 1, (kukan.second + 1) / 2, 0, 0, steven.n);
		}
		q.push_back(m.first);
		q.push_back(aikata.first);
		if (kukan.first != m.second) {
			//cout << 0 << endl;
			pq.push(pii(kukan.first, m.second));
		}
		if (m.second + 1 != aikata.second) {
			//cout << 1 << endl;
			pq.push(pii(m.second + 1, aikata.second));
		}
		if (aikata.second + 1 != kukan.second) {
			//cout << 2 << endl;
			pq.push(pii(aikata.second + 1, kukan.second));
		}
	}
	for (i = 0; i < n; i++) {
		cout << q[i] << " ";
	}
	cout << endl;
}

