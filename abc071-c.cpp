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
    	vl a(n);
    	for (i = 0; i < n; i++) {
    		cin >> a[i];
    	}
    	sort(a.begin(), a.end());
    	reverse(a.begin(), a.end());
    	ll pre = 0;
    	bool flag = false;
    	vl b;
    	for (i = 0; i < n; i++) {
    		if (flag) {
    			pre = a[i];
    			flag = false;
    		}
    		else {
    			if (pre == a[i]) {
    				b.push_back(a[i]);
    				if (b.size() == 2) {
    					break;
    				}
    				flag = true;
    				pre = a[i];
    			}
    			else {
    				pre = a[i];
    			}
    		}
    	}
    	if (b.size() == 2) {
    		cout << b[0] * b[1] << endl;
    	}
    	else {
    		cout << "0" << endl;
    	}
    	return 0;
    }