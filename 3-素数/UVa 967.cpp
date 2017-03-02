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
bool isPrime(ull a){
	set<ull>::iterator it = Primes.find(a);
	if (it == Primes.end())
		return false;
	return true;
}
bool isCircularPrime(ull a) {
	size_t w= log10(a)+1;
	for (int i = 0; i < w; ++i) {
		if (!isPrime(a))
			return false;
		a = (a % 10)*(ull)pow(10, w-1) + a / 10;
	}
	return true;
}
int main()
{
	ull _,__;
	int N = 1000000 - 1;
	vector<ull> f(N+1);
	MakePrime(N);
	for (ull i = 2; i <= N;++i) {
		if (isCircularPrime(i))
			f[i] = f[i - 1] + 1;
		else f[i] = f[i - 1];
	}
	while (cin >> _ && _!=-1) {
		cin >> __;
		size_t ans = f[__] - f[_ - 1];
		if (!ans)
			cout << "No Circular Primes." << endl;
		else if (ans == 1)
			cout << "1 Circular Prime." << endl;
		else
			cout << ans << " Circular Primes." << endl;
	}
	return 0;
}