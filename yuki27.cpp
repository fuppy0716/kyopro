// kyopro.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
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


int main() {
	vi v(4);
	int i, j, a, b, c;
	for (i = 0; i < 4; i++) {
		cin >> v[i];
	}
	int ia, ib, ic;
	sort(v.begin(), v.end());
	int m = inf;
	for (a = 1; a <= v[0]; a++) {
		for (b = a ; b <= v[3]; b++) {
			for (c = b ; c <= v[3]; c++) {
				int cnt = 0;
				for (i = 0; i < 4; i++) {
					for (ic = v[i] / c; ic >= 0; ic--) {
						for (ib = (v[i] - c*ic) / b; ib >= 0; ib--) {
							ia = 0;
							if ((v[i] - c*ic - b*ib) % a == 0) {
								ia = (v[i] - c*ic - b*ib) / a;
								cnt += ia + ib + ic;
								ia = ib = ic = -100;
							}
						}
					}
					if (ia != -100)
						break;
				}
				if (ia == -100) {
					m = min(m, cnt);
				}
			}
		}
	}
	cout << m << endl;
}