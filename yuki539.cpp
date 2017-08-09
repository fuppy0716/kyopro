
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

string incre(string s) {
	int i = 0;
	bool flag = 1;
	for (i = 0; i < s.size(); i++) {
		if (s[i] != '9')
			flag = 0;
	}
	if (flag) {
		string ans = "1";
		for (i = 0; i < s.size(); i++) {
			ans.push_back('0');
		}
		return ans;
	}
	else {
		int i = s.size() - 1;
		while (1) {
			if (s[i] != '9') {
				int a = s[i] - '0';
				a++;
				char c = a + '0';
				s[i] = c;
				break;
			}
			else {
				s[i] = '0';
				i--;
			}
		}
		return s;
	}
}

int main() {
	int t, i, j;
	scanf("%d\n", &t);
	for (i = 0; i < t; i++) {
		string head, num, tail;
		bool flag = false;
		char c;
		scanf("%c", &c);
		while (c != '\n') {
			if (!flag) {
				if (c < '0' || '9' < c)
					tail.push_back(c);
				else {
					head += (num + tail);
					num.erase(num.begin(), num.end());
					tail.erase(tail.begin(), tail.end());
					num.push_back(c);
					flag = true;
				}
			}
			else {
				if (c >= '0' && c <= '9')
					num.push_back(c);
				else {
					tail.push_back(c);
					flag = false;
				}
			}
			scanf("%c", &c);
		}
		if (!num.empty()) {
			num = incre(num);
		}
		cout << head << num << tail << endl;
	}
}