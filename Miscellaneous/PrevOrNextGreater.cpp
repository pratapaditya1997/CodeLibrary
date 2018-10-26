/*
Lmn[i] = index upto which ith element is the minimum (on the left side)
Lmx[i] = index upto which ith element is the maximum (on the left side)

Rmn[i] = index upto which ith element is the minimum (on the right side)
Rmx[i] = index upto which ith element is the maximum (on the right side)
*/

const int N = 1e6 + 6;
int n;
int a[N], Lmn[N], Lmx[N], Rmx[N], Rmn[N];

void calculate() {
	vi A, B;
	for (int i = 0; i < n; i++) {
		while (!A.empty() and a[A.back()] <= a[i]) {
			Rmx[A.back()] = i - 1;
			A.pop_back();
		}
		Lmx[i] = A.empty() ? 0 : A.back() + 1;
		A.push_back(i);
		while (!B.empty() and a[B.back()] >= a[i]) {
			Rmn[B.back()] = i - 1;
			B.pop_back();
		}
		Lmn[i] = B.empty() ? 0 : B.back() + 1;
		B.push_back(i);
	}
	while (!A.empty()) {
		Rmx[A.back()] = n - 1;
		A.pop_back();
	}
	while (!B.empty()) {
		Rmn[B.back()] = n - 1;
		B.pop_back();
	}
}
