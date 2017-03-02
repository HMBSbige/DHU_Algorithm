#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <ctime>
#define ull unsigned long long//<=18446744073709551615
#define ll long long//<=9223372036854775807
using namespace std;
vector<bool> isPrime;
vector<ull> Primes;
vector<ull> ans;

void MakePrime(ull N)//快速线性筛法
{
	++N;
	isPrime = vector<bool>(N + 1, true);
	vector<ull>().swap(Primes);
	isPrime[0] = false;
	isPrime[1] = false;
	vector<ull>sum(N+1,0);
	ans= vector<ull>(N+1);

	for (ull i = 2; i <N; ++i)
	{
		if (isPrime[i]) {
			Primes.push_back(i);
			sum[i] = i;
		}

		for (ull j = 0; j < Primes.size() && i * Primes[j] < N; j++)
		{
			isPrime[i * Primes[j]] = 0;
			if (!(i % Primes[j])) {
				sum[i * Primes[j]] = sum[i];
				break;
			}
			sum[i*Primes[j]] = sum[i] + Primes[j];
		}
		ans[i] = ans[i - 1] + isPrime[sum[i]];
	}
}
int main()
{
	ull _, __;
	MakePrime(5000000);
	while (cin >> _ && _) {
		cin >> __;
		cout << ans[__]-ans[_-1]<< endl;
	}
	return 0;
}