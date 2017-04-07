#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <bitset>
#include <sstream>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////

typedef uint64_t  ull;
class Miller_Rabin {
	//using ull = unsigned long long;
private:
	const int S;
	ull mult_mod(ull  a, ull   b, ull   c)
	{
		a %= c;
		b %= c;
		ull ret = 0;
		ull tmp = a;
		while (b)
		{
			if (b & 1)
			{
				ret += tmp;
				if (ret > c)
					ret -= c;
			}
			tmp <<= 1;
			if (tmp > c)
				tmp -= c;
			b >>= 1;
		}
		return ret;
	}
	ull  pow_mod(ull   a, ull   n, ull   mod)
	{
		ull ret = 1;
		ull temp = a%mod;
		while (n)
		{
			if (n & 1)
				ret = mult_mod(ret, temp, mod);
			temp = mult_mod(temp, temp, mod);
			n >>= 1;
		}
		return ret;
	}
	bool check(ull a, ull n, ull x, ull t)
	{
		ull ret = pow_mod(a, x, n);
		ull last = ret;
		register ull i;
		for (i = 1; i <= t; i++)
		{
			ret = mult_mod(ret, ret, n);
			if (ret == 1 && last != 1 && last != n - 1)
				return true;
			last = ret;
		}
		if (ret != 1)
			return true;
		else
			return false;
	}
public:
	Miller_Rabin() :S(10) {}
	bool isPrime(ull n)
	{
		if (n < 2)return false;
		if (n == 2)return true;
		if ((n & 1) == 0)return false;
		ull x = n - 1;
		ull t = 0;
		while ((x & 1) == 0) { x >>= 1; t++; }
		//srand((unsigned int)time(NULL));
		register int i;
		for (i = 0; i < S; i++)
		{
			ull a = rand() % (n - 1) + 1;
			if (check(a, n, x, t))
				return false;
		}
		return true;
	}
};
class Pollard_Rho {
	//using ull = unsigned long long;
public:
	Pollard_Rho() {}
	std::vector<ull> factor;
	ull minfactor(ull n) {
		std::vector<ull>().swap(factor);
		findfac(n);
		if (!factor.size()) {
			return 1;
		}
		return factor[min_element(factor.begin(), factor.end()) - factor.begin()];
	}
private:
	Miller_Rabin mr;
	ull gcd(ull a, ull b)
	{
		if (a == 0)return 1;//???????
		while (b)
		{
			ull t = a%b;
			a = b;
			b = t;
		}
		return a;
	}
	ull mult_mod(ull  a, ull   b, ull   c)
	{
		a %= c;
		b %= c;
		ull ret = 0;
		ull tmp = a;
		while (b)
		{
			if (b & 1)
			{
				ret += tmp;
				if (ret > c)
					ret -= c;
			}
			tmp <<= 1;
			if (tmp > c)
				tmp -= c;
			b >>= 1;
		}
		return ret;
	}
	ull Pollard_rho(ull x, ull c)
	{
		ull i = 1, k = 2;
		ull x0 = rand() % x;
		ull y = x0;
		while (1)
		{
			i++;
			x0 = (mult_mod(x0, x0, x) + c) % x;
			ull d = gcd(y - x0, x);
			if (d != 1 && d != x) return d;
			if (y == x0) return x;
			if (i == k) { y = x0; k += k; }
		}
	}
	void findfac(ull n)
	{
		if (n == 1) {
			factor.push_back(n);
			return;
		}
		if (mr.isPrime(n))//素数
		{
			factor.push_back(n);
			return;
		}
		ull p = n;
		while (p >= n)
			p = Pollard_rho(p, rand() % (n - 1) + 1);
		findfac(p);
		findfac(n / p);
	}
};
inline ull myunique(std::vector<ull> in) {
	ull ans = 1;
	std::vector<ull> t;
	register ull i, last;
	t.push_back(1);
	last = in[0];
	for (i = 1; i < in.size(); ++i) {
		if (in[i] != last) {
			t.push_back(1);
			last = in[i];
		}
		else {
			++t[t.size() - 1];
		}
	}
	for (i = 0; i < t.size(); ++i) {
		ans *= t[i];
	}
	return ans;
}
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef ofile	
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", std::ios::trunc);
	std::cout.rdbuf(outfile.rdbuf());
#endif
	//////////////////////////////////////////////////////////////////////
	register ull t;
	ull a, b;
	Pollard_Rho pr;
	std::cin >> t;
	while (t--) {
		std::cin >> a >> b;
		pr.minfactor(a);
		std::vector<ull> factor = pr.factor;
		sort(factor.begin(), factor.end());
		std::cout << myunique(factor) << " ";
		pr.minfactor(b);
		factor = pr.factor;
		sort(factor.begin(), factor.end());
		std::cout << myunique(factor) << std::endl;
	}
	//////////////////////////////////////////////////////////////////////
#ifdef ofile
	outfile.close();
#endif
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}