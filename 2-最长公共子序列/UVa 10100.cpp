#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int> > table;

template <class T> void vecClear(vector<T> *vec) {
	vector<T>().swap(*vec);
}
template <class T> T Reverse(T str)
{
	reverse(str.begin(), str.end());
	return str;
}
template <class T> int lcs(T X, T Y)
{
	size_t m = X.size();
	size_t n = Y.size();
	table = vector<vector<int> >(m + 1, vector<int>(n + 1));
	for (int i = 0; i<m + 1; ++i)
	{
		for (int j = 0; j<n + 1; ++j)
		{
			if (i == 0 || j == 0)
				table[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				table[i][j] = table[i - 1][j - 1] + 1;

			else
				table[i][j] = max(table[i - 1][j], table[i][j - 1]);
		}
	}
	return table[m][n];
}
bool isRight(char a) {
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
		return true;
	return false;
}
int main()
{
	size_t N = 1;
	string t_,t__;
	vector<string> _, __;
	while (getline(cin, t_, '\n')) {
		vecClear<string>(&_);
		vecClear<string>(&__);
		getline(cin, t__, '\n');
		if (t_ == "" || t__ == "") {
			cout <<setw(2)<< N++ << ". Blank!" << endl;
		}
		else {
			//
			int i = 0, j = 0;
			for (; i < t_.size(); ++i) {
				if (!isRight(t_[i])) {
					if(t_.substr(j, i - j)!="")
						_.push_back(t_.substr(j, i - j));
					j = i + 1;
				}
			}
			if (j < i)
				_.push_back(t_.substr(j, i - j));
			//
			i = 0, j = 0;
			for (; i < t__.size(); ++i) {
				if (!isRight(t__[i])) {
					if(t__.substr(j, i - j)!="")
						__.push_back(t__.substr(j, i - j));
					j = i + 1;
				}
			}
			if (j < i)
				__.push_back(t__.substr(j, i - j));
			//
			cout << setw(2) << N++ << ". Length of longest match: " << lcs<vector<string> >(_, __) << endl;
		}
	}
	return 0;
}