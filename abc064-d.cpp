#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i,a,b) for(i=a;i<b;i++)
#define rloop(i,a,b) for(i=a;i>=b;i--)
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
	int n, i;
	cin >> n;
	string s;
	cin >> s;
	string head;
	int a = 0, b = 0;
	loop(i, 0, n) {
		if (s[i] == '(') {
			a++;
		}
		else {
			b++;
		}
		if (b>a) {
			head.push_back('(');
			a++;
		}
	}
	cout << head << s;
	loop(i, 0, a - b) {
		cout << ')';
	}
	cout << endl;
}