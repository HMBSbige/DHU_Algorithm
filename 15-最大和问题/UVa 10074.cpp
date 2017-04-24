#include <iostream>
using namespace std;
int main()
{
	int m, n;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0)
			break;
		int i, j, map[100][100];
		for (i = 0; i < n; ++i)
			for (j = 0; j < m; ++j)
				cin >> map[i][j];
		int max = 0, tmp, length = 0, width = 0;
		for (i = 0; i < n; ++i)
		{
			int sum[100] = {};
			for (j = i; j < n; ++j)
			{
				for (auto k = 0; k < m; ++k)
				{
					sum[k] += !map[j][k];
					if (k == 0 || tmp != length * width)
						tmp = 0 , length = 0;
					length++ , width = j - i + 1;
					tmp += sum[k];
					if (tmp == length * width)
						max = max > tmp ? max : tmp;
				}
			}
		}
		cout << max << endl;
	}
	return 0;
}