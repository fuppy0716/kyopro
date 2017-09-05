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
	int n, i, j;
	cin >> n;
	char c;
	vi a(9, 0);
	for (i = 0; i < n; i++) {
		cin >> c;
		if (c < 'i') {
			a[0]++;
		}
		else if (c == 'i') {
			a[1]++;
		}
		else if (c < 'k') {
			a[2]++;
		}
		else if (c == 'k') {
			a[3]++;
		}
		else if (c < 'u') {
			a[4]++;
		}
		else if (c == 'u') {
			a[5]++;
		}
		else if (c < 'y') {
			a[6]++;
		}
		else if (c == 'y') {
			a[7]++;
		}
		else {
			a[8]++;
		}
	}
	int cnt = a[8];
	a[8] = 0;
	int temp = min(a[7], a[6]);
	cnt += temp;
	a[7] -= temp;
	a[6] -= temp;
	if (a[7] <= 0) {
		cout << cnt << endl;
		return 0;
	}
	temp = min(a[7], min(a[5], a[4]));
	cnt += temp;
	a[7] -= temp;
	a[5] -= temp;
	a[4] -= temp;
	if (a[7] <= 0) {
		cout << cnt << endl;
		return 0;
	}
	else if (a[5] <= 0) {
		cnt += a[7] / 2;
		cout << cnt << endl;
		return 0;
	}
	temp = min(a[7], min(a[5], min(a[3], a[2])));
	cnt += temp;
	a[7] -= temp;
	a[5] -= temp;
	a[3] -= temp;
	a[2] -= temp;
	if (a[7] <= 0) {
		cout << cnt << endl;
		return 0;
	}
	else if (a[5] <= 0) {
		cnt += a[7] / 2;
		cout << cnt << endl;
		return 0;
	}
	else if (a[3] <= 0) {
		while (a[5] >= 2 || a[7] >= 1) {
			a[5] -= 2;
			a[7] -= 1;
			cnt++;
		}
		if (a[7] >= 2) {
			cnt += a[7] / 2;
		}
		cout << cnt << endl;
		return 0;
	}
	temp = min(a[7], min(a[5], min(a[3], min(a[1], a[0]))));
	cnt += temp;
	a[7] -= temp;
	a[5] -= temp;
	a[3] -= temp;
	a[1] -= temp;
	a[0] -= temp;
	if (a[7] <= 0) {
		cout << cnt << endl;
		return 0;
	}
	else if (a[5] <= 0) {
		cnt += a[7] / 2;
		cout << cnt << endl;
		return 0;
	}
	else if (a[3] <= 0) {
		while (a[5] >= 2 && a[7] >= 1) {
			a[5] -= 2;
			a[7] -= 1;
			cnt++;
		}
		if (a[7] >= 2) {
			cnt += a[7] / 2;
		}
		cout << cnt << endl;
		return 0;
	}
	else if (a[1] <= 0) {
		while (a[3] >= 2 && a[5] >= 1 && a[7] >= 1) {
			a[3] -= 2;
			a[5]--;
			a[7]--;
			cnt++;
		}
		while (a[5] >= 2 && a[7] >= 1) {
			a[5] -= 2;
			a[7] -= 1;
			cnt++;
		}
		if (a[7] >= 2) {
			cnt += a[7] / 2;
		}
		cout << cnt << endl;
		return 0;
	}
	else {
		while (a[1] >= 2 && a[3] >= 1 && a[5] >= 1 && a[7] >= 1) {
			a[1] -= 2;
			a[3]--;
			a[5]--;
			a[7]--;
			cnt++;
		}while (a[3] >= 2 && a[5] >= 1 && a[7] >= 1) {
			a[3] -= 2;
			a[5]--;
			a[7]--;
			cnt++;
		}
		while (a[5] >= 2 && a[7] >= 1) {
			a[5] -= 2;
			a[7] -= 1;
			cnt++;
		}
		if (a[7] >= 2) {
			cnt += a[7] / 2;
		}
		cout << cnt << endl;
		return 0;
	}
}