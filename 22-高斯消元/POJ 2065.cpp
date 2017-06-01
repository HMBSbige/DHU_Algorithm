#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn  75
typedef __int64 LL;
LL det[maxn][maxn], x[maxn];
size_t  var, p;
void gauss()
{
	int k, col;
	for (k = col = 0; k<var&&col<var; ++k, ++col)
	{
		int min_i = k;
		for (int i = k + 1; i<var; ++i)//减小误差的出现
			if (det[min_i][col] < det[i][col])
				min_i = i;
		if (min_i != k)
			for (int i = col; i <= var; ++i)
				swap(det[k][i], det[min_i][i]);
		if (det[k][col] == 0)
		{
			--k;
			continue;
		}
		for (int i = k + 1; i<var; ++i)
			if (det[i][col])
			{
				LL x = det[k][col];
				LL y = det[i][col];
				for (int j = col; j <= var; ++j)
					det[i][j] = (((det[i][j] * x - det[k][j] * y) % p) + p) % p;
			}
	}
	for (int i = k - 1; i >= 0; --i)
	{
		LL temp = det[i][var];
		for (int j = i + 1; j<var; ++j)
			temp = ((temp - det[i][j] * x[j]) % p + p) % p;
		while (temp%det[i][i])
			temp += p;//保证结果的精度
		x[i] = (temp / det[i][i] % p + p) % p;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		string str;
		cin >> p >> str;
		var = str.size();
		for (int i = 0; i<var; ++i)
		{
			LL num = 1;
			for (int j = 0; j<var; ++j)
			{
				det[i][j] = num;
				num = (num * (i + 1)) % p;
			}
			if (str[i] == '*')
				det[i][var] = 0;
			else
				det[i][var] = str[i] - 'a' + 1;
		}
		gauss();
		for (int i = 0; i<var - 1; ++i)
			cout << x[i] << " ";
		cout << x[var - 1] << endl;
	}
	return 0;
}