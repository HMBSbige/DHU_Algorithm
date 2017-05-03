#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 0x7fffffff;

int main() {
	ios::sync_with_stdio(false);

	vector <int> dp1, dp2, a, front, back;
	int n;

	while (cin >> n) {
		vector <int>(n).swap(a);
		vector <int>().swap(dp1);
		dp1.push_back(-INF);
		vector <int>(n).swap(front);
		vector <int>().swap(dp2);
		dp2.push_back(-INF);
		vector <int>(n).swap(back);
		auto ans = 1;

		for (auto i = 0; i < n; ++i) {
			cin >> a[i];
		}

		for (size_t i = 0; i < a.size(); ++i) {
			if (a[i] > dp1.back()) {
				dp1.push_back(a[i]);
				front[i] = dp1.size() - 1;
			}
			else {
				auto it = lower_bound(dp1.begin(), dp1.end(), a[i]);
				*it = a[i];
				front[i] = it - dp1.begin();
			}
		}

		for (int i = a.size() - 1; i >= 0; --i) {
			if (a[i] > dp2.back()) {
				dp2.push_back(a[i]);
				back[i] = dp2.size() - 1;
			}
			else {
				auto it = lower_bound(dp2.begin(), dp2.end(), a[i]);
				*it = a[i];
				back[i] = it - dp2.begin();
			}
		}

		for (auto i = 0; i < n; ++i) {
			if (min(front[i], back[i]) * 2 - 1 > ans)
				ans = min(front[i], back[i]) * 2 - 1;
		}
		cout << ans << endl;
	}
	return 0;
}