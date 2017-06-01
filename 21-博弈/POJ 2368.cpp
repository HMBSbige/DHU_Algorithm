#include <iostream>
#include <algorithm>  
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n;
	while (cin>>n)
	{
		vector<int> sp;
		for (int i = 1; i*i <= n; ++i)
		{
			if (n%i == 0)
			{
				sp.push_back(i);
				sp.push_back(n / i);
			}
		}
		sort(sp.begin(),sp.end());
		int fp = 0;
		for (int i = 0; i < sp.size(); ++i)
		{
			if (sp[i] > 2)
			{
				fp = 1;
				cout << sp[i] - 1 << endl;
				break;
			}
		}
		if (fp == 0)
			cout << 0 << endl;
	}
	return 0;
}