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
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

void ask(vi ques) {
	cout << "? ";
	for (int i = 0; i < ques.size(); i++) {
		cout << ques[i] << " ";
	}
	cout << endl;
	fflush(stdout);
	return;
}

void answer(vi weight) {
	cout << "! ";
	for (int i = 0; i < weight.size(); i++) {
		if (weight[i] == 9 || weight[i] == 11) {
			cout << 1 << " ";
		}
		else {
			cout << 0 << " ";
		}
	}
	cout << endl;

	fflush(stdout);
	return;
}

int main() {
	int i, j, k;
	vii hyou(5, vi(13));
	for (j = 8; j <= 12; j++) {
		vi a = { j };
		for (i = 0; i < 5; i++) {
			int n = a.size();
			int x = 10;
			int sum = 0;
			for (k = 0; k < n; k++) {
				sum += a[n - k - 1] * pow(x, k);
			}
			hyou[i][j] = sum;
			a.push_back(8);
		}
	}
	/*
	for (i = 0; i < 5; i++) {
	for (j = 8; j <= 12; j++) {
	cout << hyou[i][j] << " ";
	}
	cout << endl;
	}
	*/
	//cout << "aaa" << endl;
	int n;
	cin >> n;
	vi weight(n);
	int start = 0;
	for (int i0 = 0; i0 < 10; i0++) {
		vi ques(n);
		for (i = start; i < n && i < start + 5; i++) {
			ques[i] = pow(10, i - start);
		}
		ask(ques);
		int sum;
		cin >> sum;
		for (i = min(4, n - start - 1); i >= 0; i--) {
			for (j = 12; j >= 8; j--) {
				if (sum >= hyou[i][j]) {
					weight[start + i] = j;
					break;
				}
			}
			sum -= weight[start + i] * pow(10, i);
		}
		start += 5;
	}
	//DEBUG_VEC(weight);
	answer(weight);
}