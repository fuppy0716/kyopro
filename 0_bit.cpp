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
#define pll pair<ll,ll>
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
x�̈�ԉ��ɗ����Ă���r�b�g�̋��ߕ�
x & -x;

*/


//n��kbit�\����\������
void print_bit(ll n, ll k) {
	ll m = (1LL << (k - 1));;
	while (m >= 1) {
		if ((n&m)) {
			cout << 1;
		}
		else {
			cout << 0;
		}
		m >>= 1;
	}
	cout << endl;
}

//n�̃r�b�g�\���̕����W����񋓂���B
void part(ll n) {
	ll m = n;
	do {
		print_bit(m, 8); //�����W���ɑ΂��鏈��
		m = (m - 1)&n;
	} while (m != n);
}

//{0,1,...,n-1}�Ɋ܂܂��T�C�Yk�̕����W�����
void part_size(ll n, ll k) {
	int comb = (1LL << k) - 1;
	while (comb < 1LL << n) {
		print_bit(comb, 12);
		int x = comb & -comb, y = comb + x;
		comb = ((comb & ~y) / x >> 1) | y;
	}
}



int main() {
	part(45);
	cout << endl << endl;
	part_size(10, 4);
}