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
#define N 10001
int n, a, b;

bool enough(vl c, ll t);

int main() {
	int i, j;
	cin >> n >> a >> b;
	vl h(n);
	ll sum = 0;
	loop(i, 0, n) {
		cin >> h[i];
		sum += h[i];
	}
	sort(h.begin(), h.end());
	reverse(h.begin(), h.end());
	ll left = 1, right = inf;
	while (left<right) {
		ll t = (left + right) / 2;
		if (enough(h, t)) {
			right = t;
		}
		else {
			left = t + 1;
		}
	}
	cout << left << endl;
}

bool enough(vl c, ll t) {
	int i, j;
	loop(i, 0, n) {
		c[i] -= t*b;
	}
	j = 0;
	ll cnt = 0;
	loop(i, 0, n) {
		if (c[i]>0) {
			if (c[i] % (a - b) == 0) {
				cnt += c[i] / (a - b);
			}
			else {
				cnt += (c[i] / (a - b) + 1);
			}
		}
		else {
			break;
		}
	}
	if (cnt <= t) {
		return true;
	}
	else {
		return false;
	}
}