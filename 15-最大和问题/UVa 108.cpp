#include <iostream>
using namespace std;

const int MAXN = 110;

int MaxSum(int n, int a[MAXN], int &start, int &end) {
	auto sum = 0;
	auto b = 0;
	for (auto i = 1; i <= n; i++) {
		if (b > 0)b += a[i];
		else {
			b = a[i];
			start = i;
			end = i;
		}
		if (b > sum) {
			sum = b;
			end = i;
		}
	}
	return sum;
}

int MaxSum2(int m, int n, int a[MAXN][MAXN], int &x1, int &y1, int &x2, int &y2) {
	int sum = 0, count = 0, start, end;
	auto b = new int[n + 1];
	for (auto i = 1; i <= m; i++) {
		for (auto k = 1; k <= n; k++)
			b[k] = 0;
		for (auto j = i; j <= m; j++) {
			for (auto k = 1; k <= n; k++)
				b[k] += a[j][k];
			auto max = MaxSum(n, b, start, end);
			if (max > sum) {
				if (count == 0) {
					x1 = i;
					y1 = start;
					count++;
				}
				sum = max;
				x2 = j;
				y2 = end;
			}
			else {
				count = 0;
			}
		}
	}
	return sum;
}
int main() {
	int a[MAXN][MAXN], x1, y1, x2, y2, n;
	while (cin >> n) {
		for (auto i = 1; i <= n; i++) {
			for (auto j = 1; j <= n; j++) {
				cin >> a[i][j];
			}
		}
		auto sum = MaxSum2(n, n, a, x1, y1, x2, y2);
		cout << sum << endl;
	}
	return 0;
}