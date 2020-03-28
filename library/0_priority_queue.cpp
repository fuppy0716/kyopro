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
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


class Cmp {
public:
	bool operator() (pii a, pii b) {
		if (a.first - a.second < b.first - b.second) {
			return false;
		}
		else {
			return true;
		}
	}
};
priority_queue<pii, vector<pii>, Cmp> pq;

//‚±‚ê‚Å‘å‚«‚¢‡‚Éo‚Ä‚­‚é
class Cmp2 {
public:
	bool operator() (int a, int b) {
		return a < b;
	}
};
priority_queue<int, vi, Cmp2> pq2;


int main() {
	priority_queue<int, vi, Cmp2> pq2;
	for (i = 0; i < 10; i++) {
		pq2.push(i);
	}
	while (!pq.empty()) {
		cout<<pq
	}
}