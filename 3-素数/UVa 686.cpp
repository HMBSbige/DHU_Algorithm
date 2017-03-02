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
set<ull> Primes;

void MakePrime(ull N)//膜改快速线性筛法
{
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

	set<ull>().swap(Primes);
	Primes.insert(2);

	for (ull i = 0; i<N; ++i) {
		if (p[i]) {
			Primes.insert(i + i + 3);
		}
	}
}
int main()
{
	ull _;
	int cnt;
	MakePrime((1LL<<15)-1);
	set<ull>::iterator it_, it;
	while (cin >> _ && _) {
		int cnt = 0;
		for (it = Primes.begin(); it != Primes.end() && *it<=_/2; ++it) {
			it_ = Primes.find(_ - (*it));
			if (it_ != Primes.end()) {
				++cnt;
			}
		}
		cout << cnt<<endl;
	}
	return 0;
}