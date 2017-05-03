#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
	int T, temp;
	map <int, int> pre;
	vector <int> dp;
	stack <int> ans;
	vector<int> a;

	cin >> T;
	cin.ignore(2);
	while (T--) {

		map <int, int>().swap(pre);
		vector <int>().swap(dp);
		vector <int>().swap(a);
		dp.push_back(-INF);

		string line;
		while (getline(cin, line) && line != "") {
			stringstream ss(line);
			ss >> temp;
			a.push_back(temp);
		}

		for (size_t i = 0; i < a.size(); ++i) {
			if (a[i] > dp.back()) {
				dp.push_back(a[i]);
				pre[a[i]] = dp[dp.size() - 2];
			}
			else {
				auto pos = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
				dp[pos] = a[i];
				pre[a[i]] = (pos - 1 < 0) ? -1 : dp[pos - 1];
			}
		}
		cout << "Max hits: " << dp.size() - 1 << endl;
		auto p = dp.back();
		while (p != -INF) {
			ans.push(p);
			p = pre[p];
		}
		while (!ans.empty()) {
			cout << ans.top() << endl;
			ans.pop();
		}
		if (T)
			cout << endl;
	}
	return 0;
}