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
	int n, k, i, j;
	cin >> n >> k;
	vi x(k), y(k);
	for (i = 0; i < k; i++) {
		cin >> x[i] >> y[i];
	}
	vi a(n);
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	vi b(n);
	for (i = 1; i <= n; i++) {
		int temp = i;
		for (j = 0; j < k; j++) {
			if (x[j] == temp)
				temp = y[j];
			else if (y[j] == temp)
				temp = x[j];
		}
		b[i - 1] = temp;
	}
	vi x2, y2;
	int goal, x_last = 0;
	for (goal = 1; goal <= n; goal++) {
		int start;
		for (i = 0; i < n; i++) {
			if (a[i] == goal) {
				start = i + 1;
				break;
			}
		}
		start = b[start - 1];
		if (start > goal) {
			for (i = start; i > goal; i--) {
				x2.push_back(i - 1);
				y2.push_back(i);
			}
		}
		else if (start < goal) {
			for (i = start; i < goal; i++) {
				x2.push_back(i);
				y2.push_back(i + 1);
			}
		}
		vi c = b;
		for (i = 1; i <= n; i++) {
			int temp = c[i-1];
			for (j = x_last; j < x2.size(); j++) {
				if (x2[j] == temp)
					temp = y2[j];
				else if (y2[j] == temp)
					temp = x2[j];
			}
			b[i - 1] = temp;
		}
		x_last = x2.size();
	}
	cout << x_last << endl;
	for (i = 0; i < x_last; i++) {
		cout << x2[i] << " " << y2[i] << endl;
	}
}