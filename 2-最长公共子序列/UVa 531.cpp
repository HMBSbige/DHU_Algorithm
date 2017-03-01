#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int> > table;
set<vector<string> > setOfLCS;

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
template <class T> void traceBack(size_t i, size_t j, T X, T Y, T lcs_str)
{
	while (i>0 && j>0)
	{
		if (X[i - 1] == Y[j - 1])
		{
			lcs_str.push_back(X[i - 1]);
			--i;
			--j;
		}
		else
		{
			if (table[i - 1][j] > table[i][j - 1])
				--i;
			else if (table[i - 1][j] < table[i][j - 1])
				--j;
			else
			{
				if (!setOfLCS.empty())//只找出一组
					return;
				traceBack<T>(i - 1, j, X, Y, lcs_str);
				traceBack<T>(i, j - 1, X, Y, lcs_str);
				return;
			}
		}
	}
	setOfLCS.insert(Reverse<T>(lcs_str));
}
int main()
{
	vector<string> _, __, temp;
	string str;
	while (cin >> str) {
		vecClear<string>(&_);
		vecClear<string>(&__);
		vecClear<string>(&temp);
		set<vector<string> >().swap(setOfLCS);//setOfLCS.clear();
		while (str != "#") {
			_.push_back(str);
			cin >> str;
		}
		cin >> str;
		while (str != "#") {
			__.push_back(str);
			cin >> str;
		}
		lcs<vector<string> >(_, __);
		traceBack<vector<string> >(_.size(), __.size(), _, __, temp);
		//
		set<vector<string> >::iterator it = setOfLCS.begin();
		for (int i = 0; i<(*it).size(); ++i) {
			if (i != 0)
				cout << " ";
			cout << (*it)[i] ;
		}
		cout << endl;
	}
	return 0;
}