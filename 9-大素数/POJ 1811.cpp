#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <climits>
#include <ctime>
using namespace std;
//#define DEBUG
#ifdef DEBUG
#include <fstream>
ofstream outfile;
#endif // DEBUG
/////////////////////////////////////////////////
//using ull = unsigned long long;
typedef unsigned long long ull;
class Miller_Rabin{
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
	Miller_Rabin():S(8){}
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
	Pollard_Rho(){}
	vector<ull> factor;
	ull minfactor(ull n) {
		vector<ull>().swap(factor);
		findfac(n);
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

int main()
{
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef DEBUG
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", ios::trunc);
#endif // DEBUG
	///////////////////////////////////
	ull n;
	Miller_Rabin mr;
	Pollard_Rho pr;
	register ull T;
	cin >> T;
	while (T--) {
		cin >> n;
		if (mr.isPrime(n))
			cout << "Prime" << endl;
		else {
			cout << pr.minfactor(n) << endl;
		}
			
	}
	///////////////////////////////////
#ifdef DEBUG
	outfile.close();
	system("pause");
#endif // DEBUG
	return 0;
}