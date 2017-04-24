#include <iostream>
using namespace  std;

int main() {
	ios::sync_with_stdio(false);
	int T, cases = 0;
	int n, x;
	cin>>T;
	while (T--) {
		cin >> n;
		auto tmp = 1, st = 0xffff, ed = 0, sum = 0, ans = 0;
		for (auto i = 2; i <= n; i++) {
			cin >> x;
			sum += x;
			if (sum < 0) sum = 0, tmp = i;
			if (sum >= ans) {

				if (sum > ans || (sum == ans && (i - tmp > ed - st))) {
					st = tmp;
					ed = i;
				}
				ans = sum;
			}
		}
		if (ans > 0)
			cout << "The nicest part of route " << ++cases << " is between stops " << st << " and " << ed << endl;
		else
			cout << "Route "<<++cases<<" has no nice parts"<<endl;
	}
	return 0;
}