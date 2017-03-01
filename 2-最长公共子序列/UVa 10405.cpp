#include <iostream>
#include <vector>
#include <string>
using namespace std;
template<class T> int LCS(T A, T B) {
	int n1 = A.size();
	int n2 = B.size();
	vector<vector<int> > dp(n1 + 1);
	for (int i = 0; i <= n1; ++i)
		dp[i].resize(n2 + 1, 0);
	for (int i = 1; i <= n1; ++i) {
		for (int j = 1; j <= n2; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (dp[i][j - 1]>dp[i][j])
				dp[i][j] = dp[i][j - 1];
			if (A[i] == B[j] && (dp[i - 1][j - 1] + 1>dp[i][j]))
				dp[i][j] = dp[i - 1][j - 1] + 1;
		}
	}
	return dp[n1][n2];
}
int main()
{
	string _, __;
	while (getline(cin,_,'\n') && getline(cin, __, '\n'))
		cout << LCS<string>("0" + _, "0" + __) - 1 << endl;
	return 0;
}