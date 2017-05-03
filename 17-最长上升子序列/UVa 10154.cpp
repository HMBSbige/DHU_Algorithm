#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

struct node {
	int w, s;
	node(int w1, int s1) {
		w = w1;  s = s1;
	}
	friend bool operator<(const node a, const node b) {
		return a.s < b.s;
	}
};

int main() {
	ios::sync_with_stdio(false);
	vector <node> turtle(1, node(0, INF));

	int x, y;
	while (cin >> x >> y)
		turtle.push_back(node(x, y));

	vector<vector<int> > dp(turtle.size(), vector<int>(turtle.size(), INF));
	dp[0][0] = 0;

	sort(turtle.begin() + 1, turtle.end());
	for (size_t i = 1; i < turtle.size(); ++i) {
		for (size_t j = 1; j <= i; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (turtle[i].s >= dp[i - 1][j - 1] + turtle[i].w) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + turtle[i].w);
			}
		}
	}

	size_t  ans = 0;
	for (auto i = turtle.size() - 1; i >= 1; --i) {
		if (dp[turtle.size() - 1][i] != INF) {
			ans = i;
			break;
		}
	}
	cout << ans << endl;
	return 0;
}