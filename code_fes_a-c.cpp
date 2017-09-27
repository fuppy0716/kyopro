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
	int h, w, i, j;
	cin >> h >> w;
	vi cnt(26);
	for (i = 0; i<h*w; i++) {
		char c;
		cin >> c;
		cnt[c - 'a']++;
	}
	vi cnt2(26);
	int sum = 0;
	for (i = 0; i<26; i++) {
		cnt2[i] = cnt[i] % 4;
		sum += cnt2[i];
	}
	bool flag = true;
	if (w % 2 == 0 && h % 2 == 0) {
		if (sum != 0) {
			flag = false;
		}
	}
	else if (w % 2 == 1 && h % 2 == 0) {
		if (sum > h) {
			flag = false;
		}
		for (i = 0; i<26; i++) {
			if (cnt2[i] % 2 == 1) {
				flag = false;
			}
		}
	}
	else if (w % 2 == 0 && h % 2 == 1) {
		if (sum > w) {
			flag = false;
		}
		for (i = 0; i<26; i++) {
			if (cnt2[i] % 2 == 1) {
				flag = false;
			}
		}
	}
	else {
		if (sum > h + w - 1) {
			flag = false;
		}
		int cnt3 = 0;
		for (i = 0; i<26; i++) {
			if (cnt2[i] % 2) {
				cnt3++;
			}
		}
		if (cnt3>1) {
			flag = false;
		}
	}
	if (flag) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

}
