#define vd vector<double>
#define vdd vector< vector<double> >
const double EPS = 1E-8;

//Ax = b������
//�����Ȃ����A��ӂłȂ��ꍇ�͒���0�̔z���Ԃ�
//A:n*n�s��
vd gauss_jordan(vdd A, vd b) {
	int n = A.size(), i, j;
	vdd B(n, vd(n + 1));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		}
	}
	for (i = 0; i < n; i++) {
		B[i][n] = b[i];
	}

	for (i = 0; i < n; i++) {
		//���ڂ��Ă���ϐ��̌W���̐�Βl���傫������i�ԖڂɎ����Ă���
		int pivot = i;
		for (j = i; j < n; j++) {
			if (abs(B[j][i]) > abs(B[pivot][i])) {
				pivot = j;
			}
		}
		swap(B[i], B[pivot]);
		if (abs(B[i][i]) < EPS) return vd();

		for (j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
		B[i][i] = 1;
		for (j = 0; j < n; j++) {
			if (i != j) {
				for (int k = i + 1; k <= n; k++) {
					B[j][k] -= B[j][i] * B[i][k];
				}
			}
		}
	}
	vd x(n);
	for (i = 0; i < n; i++) {
		x[i] = B[i][n];
	}
	return x;
}

int main() {
	int n, i, j;
	cin >> n;
	vdd A(n, vd(n));
	vd b(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cin >> A[i][j];
		}
		cin >> b[i];
	}
	vd ans = gauss_jordan(A, b);
	DEBUG_VEC(ans);
}