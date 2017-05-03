#include <iostream>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int num[3][3], cnt[6];
	const string outputString[6] = { "BCG", "BGC", "CBG", "CGB", "GBC", "GCB" };

	while (cin >>
		num[0][0] >> num[0][1] >> num[0][2] >>
		num[1][0] >> num[1][1] >> num[1][2] >>
		num[2][0] >> num[2][1] >> num[2][2]) {
		auto mini = 0;
		auto sum = 0;
		for (auto i = 0; i<3; ++i)
			for (auto j = 0; j<3; ++j)
				sum += num[i][j];

		cnt[0] = sum - num[0][0] - num[1][2] - num[2][1];
		cnt[1] = sum - num[0][0] - num[1][1] - num[2][2];
		cnt[2] = sum - num[0][2] - num[1][0] - num[2][1];
		cnt[3] = sum - num[0][2] - num[1][1] - num[2][0];
		cnt[4] = sum - num[0][1] - num[1][0] - num[2][2];
		cnt[5] = sum - num[0][1] - num[1][2] - num[2][0];

		for (auto i = 0; i < 6; ++i)
			if (cnt[i] < cnt[mini])
				mini = i;

		cout << outputString[mini] << " " << cnt[mini] << endl;
	}
	return 0;
}