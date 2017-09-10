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
    	int n, i;
    	cin >> n;
    	vl a(n);
    	for (i = 0; i < n; i++) {
    		cin >> a[i];
    	}
    	if (n == 1) {
    		cout << 1 << endl;
    		return 0;
    	}
    	sort(a.begin(), a.end());
    	ll cnt1 = 0, cnt2 = 1;
    	ll pre = a[0];
    	for (i = 1; i < n; i++) {
    		if (pre == a[i]) {
    			cnt2++;
    		}
    		else {
    			if (cnt2 % 2 == 1) {
    				cnt1++;
    			}
    			pre = a[i];
    			cnt2 = 1;
    		}
    	}
    	if (cnt2 % 2 == 1) {
    		cnt1++;
    	}
    	cout << cnt1 << endl;
    }