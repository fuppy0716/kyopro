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

int main() {
	int n;
	cin >> n;
	int i, j;
	map<int, int> right;
	vi a(n);
	for (i = 0; i < n; i++) {
		cin >> a[i];
		right[a[i]] = i;
	}
	vi b(n);
	set<int> st;
	for (i = 0; i < n; i++) {
		st.insert(a[i]);
		b[i] = *st.rbegin();
		if (right[a[i]] == i) {
			st.erase(a[i]);
		}
	}
	for (i = 0; i < n; i++) {
		cout << b[i] << " ";
	}
	cout << endl;
}




#define N 200010
const int DAT_SIZE = (1 << 18) - 1;
int n, q;
vl a(N);
vl node(DAT_SIZE), lazy(DAT_SIZE, 0);

void init(int k, int l, int r) {
	int _n = 1; while (_n < n) _n *= 2;
	node.resize(2 * _n - 1);
	lazy.resize(2 * _n - 1, 0);
	for (int i = 0; i < n; i++) node[i + _n - 1] = a[i];
	for (int i = _n - 2; i >= 0; i--) node[i] = node[i * 2 + 1] + node[i * 2 + 2];
	n = _n;
}

// k�Ԗڂ̃m�[�h�ɂ��Ēx���]�����s��
inline void eval(int k, int l, int r) {
	// �x���z�񂪋�łȂ��ꍇ�A���m�[�h�y�юq�m�[�h�ւ�
	// �l�̓`�d���N����
	if (lazy[k] != 0) {
		node[k] = lazy[k] * (r - l); /////

									 // �ŉ��i���ǂ����̃`�F�b�N�����悤
									 // �q�m�[�h�͐e�m�[�h�� 1/2 �͈̔͂ł��邽�߁A
									 // �`�d������Ƃ��͔����ɂ���
		if (r - l > 1) {
			lazy[2 * k + 1] = lazy[k]; /////
			lazy[2 * k + 2] = lazy[k]; /////
		}

		// �`�d���I������̂ŁA���m�[�h�̒x���z�����ɂ���
		lazy[k] = 0;
	}
}

void change(int a, int b, ll x, int k, int l, int r) {

	// k �Ԗڂ̃m�[�h�ɑ΂��Ēx���]�����s��
	eval(k, l, r);

	// �͈͊O�Ȃ牽�����Ȃ�
	if (b <= l || r <= a) return;

	// ���S�ɔ핢���Ă���Ȃ�΁A�x���z��ɒl����ꂽ��ɕ]��
	if (a <= l && r <= b) {
		lazy[k] = x; //////
		eval(k, l, r);
	}

	// �����łȂ��Ȃ�΁A�q�m�[�h�̒l���ċA�I�Ɍv�Z���āA
	// �v�Z�ς݂̒l��������Ă���
	else {
		change(a, b, x, 2 * k + 1, l, (l + r) / 2);
		change(a, b, x, 2 * k + 2, (l + r) / 2, r);
		node[k] = node[2 * k + 1] + node[2 * k + 2];
	}
}

ll getsum(int a, int b, int k, int l, int r) {

	// �֐����Ăяo���ꂽ��܂��]���I
	eval(k, l, r);

	if (b <= l || r <= a) return 0;
	if (a <= l && r <= b) return node[k];
	ll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
	ll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
	return resl + resr;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	set<int> st;
	map<int, int> left, right;
	for (i = 0; i < n; i++) {
		st.insert(a[i]);
		if (left[a[i]] == 0) {
			left[a[i]] = i + 1;
		}
		right[a[i]] = i + 1;
	}
	for (auto itr = st.begin(); itr != st.end(); itr++) {
		int x = *itr;
		change(left[x] - 1, right[x], x, 0, 0, n);
	}
	for (i = 0; i < n; i++) {
		cout << getsum(i, i + 1, 0, 0, n) << " ";
	}
	cout << endl;
}