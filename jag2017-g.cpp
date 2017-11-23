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
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define P complex<double>

// ���e����덷��
#define EPS (1e-5)
// 2�̃X�J���[�����������ǂ���
#define EQ(a,b) (abs((a)-(b)) < EPS)
// 2�̃x�N�g�������������ǂ���
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) )

/*
// �x�N�g��a�̐�Βl�����߂�
double length = abs(a);

// 2�_a,b�Ԃ̋��������߂�
double distance = abs(a-b);

// �x�N�g��a�̒P�ʃx�N�g�������߂�
P b = a / abs(a);

// �x�N�g��a�̖@���x�N�g��n1,n2�����߂�
P n1 = a * P(0, 1);
P n2 = a * P(0, -1);
// �x�N�g��a�̒P�ʖ@���x�N�g��un1,un2�����߂�
P un1 = (a * P(0, +1)) / abs(a);
P un2 = (a * P(0, -1)) / abs(a);
*/

// ���� (dot product) : a�Eb = |a||b|cos��
double dot(P a, P b) {
	return (a.real() * b.real() + a.imag() * b.imag());
}

// �O�� (cross product) : a�~b = |a||b|sin��
double cross(P a, P b) {
	return (a.real() * b.imag() - a.imag() * b.real());
}

// 2�����̒��𔻒� : a��b <=> dot(a, b) = 0
int is_orthogonal(P a1, P a2, P b1, P b2) {
	return EQ(dot(a1 - a2, b1 - b2), 0.0);
}

// 2�����̕��s���� : a//b <=> cross(a, b) = 0
int is_parallel(P a1, P a2, P b1, P b2) {
	return EQ(cross(a1 - a2, b1 - b2), 0.0);
}

// �_c������a,b��ɂ��邩�Ȃ���
int is_point_on_line(P a, P b, P c) {
	return EQ(cross(b - a, c - a), 0.0);
}

// �_c������a,b��ɂ��邩�Ȃ���
int is_point_on_lines(P a, P b, P c) {
	// |a-c| + |c-b| <= |a-b| �Ȃ������
	return (abs(a - c) + abs(c - b) < abs(a - b) + EPS);
}

// �_a,b��ʂ钼���Ɠ_c�Ƃ̋���
double distance_l_p(P a, P b, P c) {
	return abs(cross(b - a, c - a)) / abs(b - a);
}

// �_a,b��[�_�Ƃ�������Ɠ_c�Ƃ̋���
double distance_ls_p(P a, P b, P c) {
	if (dot(b - a, c - a) < EPS) return abs(c - a);
	if (dot(a - b, c - b) < EPS) return abs(c - b);
	return abs(cross(b - a, c - a)) / abs(b - a);
}

// a1,a2��[�_�Ƃ��������b1,b2��[�_�Ƃ�������̌�������
int is_intersected_ls(P a1, P a2, P b1, P b2) {
	return (cross(a2 - a1, b1 - a1) * cross(a2 - a1, b2 - a1) < EPS) &&
		(cross(b2 - b1, a1 - b1) * cross(b2 - b1, a2 - b1) < EPS);
}

// a1,a2��[�_�Ƃ��������b1,b2��[�_�Ƃ�������̌�_�v�Z
P intersection_ls(P a1, P a2, P b1, P b2) {
	P b = b2 - b1;
	double d1 = abs(cross(b, a1 - b1));
	double d2 = abs(cross(b, a2 - b1));
	double t = d1 / (d1 + d2);

	return a1 + (a2 - a1) * t;
}

// a1,a2��ʂ钼����b1,b2��ʂ钼���̌�������
int is_intersected_l(P a1, P a2, P b1, P b2) {
	return !EQ(cross(a1 - a2, b1 - b2), 0.0);
}

// a1,a2��ʂ钼����b1,b2��ʂ钼���̌�_�v�Z
P intersection_l(P a1, P a2, P b1, P b2) {
	P a = a2 - a1; P b = b2 - b1;
	return a1 + a * cross(b, b1 - a1) / cross(b, a);
}

int main() {
	int n, i, j;
	cin >> n;
	vector<double> r(n);
	vector<P> s(n), g(n);
	P a;
	for (i = 0; i < n; i++) {
		int r2, x1, y1, x2, y2;
		cin >> r2 >> x1 >> y1 >> x2 >> y2;
		r[i] = r2;
		s[i].real(x1); s[i].imag(y1);
		g[i].real(x2); g[i].imag(y2);
	}
	vector<bool> dp((1 << n), false);
	dp[0] = true;
	int ans = 0;
	for (i = 0; i < (1 << n); i++) {
		if (!dp[i]) {
			continue;
		}
		int cnt = 0;
		for (int tmp = 1; tmp < (1 << n); tmp <<= 1) {
			if (i & tmp) {
				cnt++;
			}
		}
		ans = max(ans, cnt);
		for (j = 0; j < n; j++) {
			if ((i & (1 << j))) {
				continue;
			}
			bool flag = true;
			for (int k = 0; k < n; k++) {
				if (j == k) {
					continue;
				}
				P b;
				if ((i & (1 << k))) {
					b = g[k];
				}
				else {
					b = s[k];
				}
				if (distance_ls_p(s[j], g[j], b) <= r[j] + r[k]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				dp[(i | (1 << j))] = true;
			}
		}
	}
	cout << ans << endl;
}