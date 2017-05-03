#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;

struct Node {
	int a, b, s, h;
	friend bool operator<(const Node a, const Node b) {
		return a.s > b.s;
	}
	Node(int a1, int b1, int h1) {
		a = a1; b = b1; s = a1 * b1; h = h1;
	}
};

int main() {
	ios::sync_with_stdio(false);
	int T = 1, n;
	vector <Node> block;

	while (cin >> n && n) {
		vector <Node>().swap(block);
		block.push_back(Node(INF, INF, 0));
		int x[35], y[35], z[35];
		for (auto i = 0; i < n; ++i) {
			cin >> x[i] >> y[i] >> z[i];
			block.push_back(Node(x[i], y[i], z[i]));
			block.push_back(Node(x[i], z[i], y[i]));
			block.push_back(Node(y[i], z[i], x[i]));
			block.push_back(Node(y[i], x[i], z[i]));
			block.push_back(Node(z[i], x[i], y[i]));
			block.push_back(Node(z[i], y[i], x[i]));
		}

		vector<int>height(block.size(), 0);
		sort(block.begin() + 1, block.end());
		for (size_t i = 0; i < block.size(); ++i) {
			for (size_t j = 0; j < i; ++j) {
				if (block[i].a < block[j].a && block[i].b < block[j].b) {
					if (height[j] + block[i].h > height[i]) {
						height[i] = height[j] + block[i].h;
					}
				}
			}
		}
		auto ans = 0;
		for (size_t i = 1; i < block.size(); i++) {
			if (height[i] > ans)
				ans = height[i];
		}
		cout << "Case " << T++ << ": maximum height = " << ans << endl;
	}
	return 0;
}