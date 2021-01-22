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
#define EPS (1e-10)
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

// 偏角ソートのための比較関数、syouは象限
int syou(pll a) {
  int x = a.first, y = a.second;
  if (x > 0 and y >= 0) return 1;
  else if (x <= 0 and y > 0) return 2;
  else if (x < 0 and y <= 0) return 3;
  else return 4;
}
bool cmp(pll a, pll b) {
  int ta = syou(a), tb = syou(b);
  if (ta != tb) return ta < tb;
  ll ax = a.first, ay = a.second;
  ll bx = b.first, by = b.second;
  if (ta == 2 or ta == 3) {
    ax *= -1; ay *= -1;
    bx *= -1; by *= -1;
  }
  ay *= bx; by *= ax;
  return ay < by;
}

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

//�Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�
//0<=theta<=180�͈̔͂ŕԂ�
double AngleOf2Vector(P A, P B)
{
	double theta = acos(dot(A, B) / (abs(A)*abs(B)));
	theta *= 180.0 / pi;
	return theta;
}

// https://poporix.hatenablog.com/entry/2020/03/03/223631
vector<P> intersection_circle(P c1, P c2, double r1, double r2) {
	double d = abs(c1 - c2);
	if (d > r1 + r2 + EPS) {
		return vector<P>(0);
	}
	double cos_theta = (r2 * r2 - r1 * r1 - d * d) / (-2 * r1 * d);
	cos_theta = max(-1., min(1., cos_theta));
	double sin_theta = sqrt(1 - cos_theta * cos_theta);
	P e = (c2 - c1) / d;

	vector<P> res;
	P temp;
	temp.real(e.real() * cos_theta - e.imag() * sin_theta);
	temp.imag(e.real() * sin_theta + e.imag() * cos_theta);
	res.push_back(temp);
	if (abs(sin_theta) > EPS) {
		temp.real(e.real() * cos_theta + e.imag() * sin_theta);
		temp.imag(-e.real() * sin_theta + e.imag() * cos_theta);
		res.push_back(temp);
	}
	return res;
}

// https://poporix.hatenablog.com/entry/2020/03/03/223631
// 誤差のこと考えてない
vector<P> intersection_circle(P c1, P c2, long double r1, long double r2) {
	long double d = abs(c1 - c2);
	if (d > r1 + r2) {
		return vector<P>(0);
	}
	long double cos_theta = (r2 * r2 - r1 * r1 - d * d) / (-2 * r1 * d);
	cos_theta = max((long double)-1., min((long double)1., cos_theta));
	long double sin_theta = sqrtl(1 - cos_theta * cos_theta);
	P e = (c2 - c1) / d * r1;

	vector<P> res;
	P temp;
	temp.real(e.real() * cos_theta - e.imag() * sin_theta);
	temp.imag(e.real() * sin_theta + e.imag() * cos_theta);
	res.push_back(temp + c1);
	if (abs(sin_theta) > EPS) {
		temp.real(e.real() * cos_theta + e.imag() * sin_theta);
		temp.imag(-e.real() * sin_theta + e.imag() * cos_theta);
		res.push_back(temp + c1);
	}
	return res;
}
