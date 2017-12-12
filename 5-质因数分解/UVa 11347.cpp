#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#define ll long long
#define ull unsigned long long
using namespace std;
const int INF = INT_MAX;
set<ull> Prime;
vector<ull> Primes;
vector<bool> isPrime;
void MakePrime(ull N)//膜改快速线性筛法
{
	ull m = N;
	--N;
	N /= 2;
	ull sn = (ull)(sqrt(2 * N) / 2);
	vector<bool> p(N, 1);
	for (ull i = 0; i < sn; i++) {
		if (p[i])
		{
			for (ull j = i*(2 * i + 6) + 3; j<N; j += 2 * i + 3)
				p[j] = false;
		}
	}
	//
	vector<ull>(1, 2).swap(Primes);
	set<ull>().swap(Prime);
	isPrime = vector<bool>(m + 1, false);
	Prime.insert(2);
	isPrime[2] = true;
	for (ull i = 0; i<N; ++i) {
		if (p[i]) {
			Primes.push_back(i + i + 3);
			Prime.insert(i + i + 3);
			isPrime[i + i + 3] = true;
		}
	}
}
int main()
{
	int t, n, k; //不小心把n定义为无符号数，结果TLE了一晚上
	string s;
	MakePrime(1000);
	cin >> t;
	for (int _ = 1; _ <= t; ++_)
	{
		cin >> n >> s;
		k = s.size();
		vector<ull> b(Primes.size(), 0);

		for (; n > 1; n -= k)
		{
			int temp = n;
			for (int i = 0; temp > 1 && i < Primes.size(); ++i)
			{
				while (!(temp % Primes[i]))
				{
					temp /= Primes[i];
					++b[i];
				}
			}
		}

		ull ans = 1;
		for (int i = 0; i < b.size(); ++i)
		{
			ans *= b[i] + 1;
			if (ans > (ull)1e18)
			{
				cout << "Case " << _ << ": Infinity" << endl;
				goto END;
			}
		}
		cout << "Case " << _ << ": " << ans << endl;
	END:;
	}
	return 0;
}