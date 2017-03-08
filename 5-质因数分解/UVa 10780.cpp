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
template<class T> void factor(T n, vector<pair<T, T> > &a) {
	T temp, i, now;
	temp = Primes.size();
	now = n;
	for (i = 0; now > 1 && i < temp; ++i)
		if (now%Primes[i] == 0) {
			a.push_back(make_pair(Primes[i], 0));
			while (now%Primes[i] == 0) {
				++get<1>(*(a.end() - 1));
				now /= Primes[i];
			}
		}
	if (now != 1)
		a.push_back(make_pair(now, 1));
}
int fakefactor(int m, int n) {
	int ans=0;
	if (n%m == 0)
		while (n%m == 0) {
			++ans;
			n /= m;
		}	
	return ans;
}
int main() {
	int m, n,ans,t;
	MakePrime(10000);
	cin >> t;
	for (int j = 1; j <= t; ++j) {
		cin >> m >> n;
		vector<pair<int, int> > a;
		factor<int>(m, a);
		vector<int> b(a.size(), 0);
		ans = INF;
		for (int k = n; k > 1; --k)
			for (int i = 0; i <a.size(); ++i)
				b[i]+= fakefactor(a[i].first, k);
		for (int i = 0; i < a.size(); ++i) {
			if (!b[i]) {
				ans = 0;
				goto OUTPUT;
			}
			ans = min(ans, b[i] / a[i].second);
		}
		OUTPUT:
		cout << "Case " << j << ":" << endl;
		if (ans)
			cout << ans << endl;
		else
			cout << "Impossible to divide" << endl;
	}
	//system("pause");
	return 0;
}