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
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };



#define N 100010
const int DAT_SIZE = (1 << 18) - 1;
int n, q;
vl a(N);
vector<pll> node(DAT_SIZE), lazy(DAT_SIZE, pll(0, 0));

// k�Ԗڂ̃m�[�h�ɂ��Ēx���]�����s��
inline void eval(int k, int l, int r) {
	// �x���z�񂪋�łȂ��ꍇ�A���m�[�h�y�юq�m�[�h�ւ�
	// �l�̓`�d���N����
	if (lazy[k] != pll(0, 0)) {
		node[k].first = (r - l) * lazy[k].first;
		node[k].second = (r - l) * lazy[k].second;

		if (r - l > 1) {
			lazy[2 * k + 1].first = lazy[k].first; /////
			lazy[2 * k + 1].second = lazy[k].second;
			lazy[2 * k + 2].first = lazy[k].first; /////
			lazy[2 * k + 2].second = lazy[k].second; /////
		}

		// �`�d���I������̂ŁA���m�[�h�̒x���z�����ɂ���
		lazy[k] = pll(0, 0);
	}
}

void update(int a, int b, ll x, int k, int l, int r) {

	// k �Ԗڂ̃m�[�h�ɑ΂��Ēx���]�����s��
	eval(k, l, r);

	// �͈͊O�Ȃ牽�����Ȃ�
	if (b <= l || r <= a) return;

	// ���S�ɔ핢���Ă���Ȃ�΁A�x���z��ɒl����ꂽ��ɕ]��
	if (a <= l && r <= b) {
		if (x == 1) {
			lazy[k].first = 1;
			lazy[k].second = 0;
		}
		else if (x == 2) {
			lazy[k].first = 0;
			lazy[k].second = 1;
		}
		eval(k, l, r);
	}

	// �����łȂ��Ȃ�΁A�q�m�[�h�̒l���ċA�I�Ɍv�Z���āA
	// �v�Z�ς݂̒l��������Ă���
	else {
		update(a, b, x, 2 * k + 1, l, (l + r) / 2);
		update(a, b, x, 2 * k + 2, (l + r) / 2, r);
		node[k].first = node[2 * k + 1].first + node[2 * k + 2].first;
		node[k].second = node[2 * k + 1].second + node[2 * k + 2].second;
	}
}

pll getsum(int a, int b, int k, int l, int r) {

	// �֐����Ăяo���ꂽ��܂��]���I
	eval(k, l, r);

	if (b <= l || r <= a) return pll(0, 0);
	if (a <= l && r <= b) return node[k];
	pll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
	pll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
	return pll(resl.first + resr.first, resl.second + resr.second);
}

int main() {
	int q, i, j;
	cin >> n >> q;
	ll scorea = 0, scoreb = 0;
	for (int unko = 0; unko < q; unko++) {
		int x, l, r;
		cin >> x >> l >> r;
		if (x == 0) {
			pll score = getsum(l, r + 1, 0, 0, n);
			if (score.first > score.second) {
				scorea += score.first;
			}
			else if (score.first < score.second) {
				scoreb += score.second;
			}
		}
		else {
			update(l, r + 1, x, 0, 0, n);
		}
		//cout << scorea << " " << scoreb << endl;
		//pll score = getsum(0, n, 0, 0, n);
		//cout << score.first << " " << score.second << endl << endl;
	}
	pll score = getsum(0, n, 0, 0, n);
	scorea += score.first;
	scoreb += score.second;
	cout << scorea << " " << scoreb << endl;
}