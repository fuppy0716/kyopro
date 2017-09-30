#include "bits/stdc++.h"
#include <unordered_set>
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

/*
cin.tie(0);
ios::sync_with_stdio(false);
*/
int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<string> s(4);
	s[0] = "##";
	s[1] = "#.";
	s[2] = ".#";
	s[3] = "..";
	bool right = false;
	string r = "F";
	int cnt = 0;
	string s1, s2;
	while (r != "end") {
		if (r == "T") {
			if (!right) {
				s1 += s[cnt][0];
				s2 += s[cnt][1];
			}
			else {
				s1 = s[cnt][0] + s1;
				s2 = s[cnt][1] + s2;
			}
			cnt = 0;
		}
		else {
			cnt++;
			if (cnt == 4) {
				right = true;
				cnt = 0;
			}
		}
		if (!right) {
			cout << s1 << s[cnt][0] << endl;
			cout << s2 << s[cnt][1] << endl;
			fflush(stdout);
		}
		else {
			cout << s[cnt][0] << s1 << endl;
			cout << s[cnt][1] << s2 << endl;
			fflush(stdout);
		}
		cin >> r;
		if (r == "end") {
			return 0;
		}
	}
}