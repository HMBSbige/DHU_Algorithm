#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	int n, x[128], y[128];
	auto cases = 0;
	while (cin>>n && n) {
		map<int, int> Rx, Ry;
		for (auto i = 0; i < n; i++) {
			cin >> x[i]>>y[i];
			Rx[x[i]] = 0, Ry[y[i]] = 0;
		}

		auto size = 0;
		for (auto it = Rx.begin();
			it != Rx.end(); ++it) {
			it->second = size++;
		}
		auto R = size;
		size = 0;
		for (auto it = Ry.begin();
			it != Ry.end(); ++it) {
			it->second = size++;
		}
		auto C = size;

		int g[128][128] = {}, ret = 0;
		for (auto i = 0; i < n; ++i) {
			int r, c;
			r = Rx[x[i]], c = Ry[y[i]];
			g[r][c]++;
		}

		for (auto i = 0; i < R; ++i) {
			int sum[128] = {}, s1, s2, mn;
			for (auto j = i; j < R; ++j) {
				s1 = s2 = 0, mn = 0;
				for (auto k = 0; k < C; ++k) {
					sum[k] += g[j][k];
					s1 += g[i][k], s2 += g[j][k];
					if (i != j) {
						ret = max(ret, s1 + s2 - mn + sum[k] - g[i][k] - g[j][k]);
						mn = min(mn, s1 + s2 - sum[k]);
					}
				}
			}
		}

		for (auto i = 0; i < R; ++i) {
			auto sum = 0;
			for (auto j = 0; j < C; ++j)
				sum += g[i][j];
			ret = max(ret, sum);
		}

		for (auto i = 0; i < C; ++i) {
			auto sum = 0;
			for (auto j = 0; j < R; ++j)
				sum += g[j][i];
			ret = max(ret, sum);
		}
		cout << "Case " << ++cases << ": " << ret << endl;
	}
	return 0;
}