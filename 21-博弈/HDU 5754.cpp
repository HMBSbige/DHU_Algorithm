#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int t, m, n;
int T;
int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--)
	{
		cin >>t >> n >> m;
		if (n>m)
			swap(n, m);
		if (t == 1)//王
		{
			--n;
			--m;
			if (n % 2 == 0 && m % 2 == 0)
				cout << "G" << endl;
			else
				cout << "B" << endl;
		}
		else if (t == 2)//车
		{
			--n;
			--m;
			if ((n^m) == 0) 
				cout << "G" << endl;
			else 
				cout << "B" << endl;
		}
		else if (t == 3)//马
		{
			--n;
			--m;
			if (n % 3 == 0 && n == m)
				cout << "G" << endl;
			else if (m % 3 == 2 && m - n == 1)
				cout << "B" << endl;
			else 
				cout << "D" << endl;
		}
		else if (t == 4)//后 威佐夫博弈
		{
			--n;
			--m;
			if (n<m)
			{
				int tmp = n;
				n = m;
				m = tmp;
			}
			int k = n - m;
			n = int(k * (1 + sqrt(5)) / 2.0);
			if (n == m)
				cout << "G" << endl;
			else
				cout << "B" << endl;
		}
	}
	return 0;
}