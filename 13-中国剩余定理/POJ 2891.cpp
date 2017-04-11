#include <iostream> 
#include <cmath>
#include <vector>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
typedef unsigned long long ull;
typedef long long ll;
ll gcdcore(ll a, ll b) {
	if (a == 0) return b;
	if (b == 0) return a;
	while ((a & 0x1) == 0) {
		a = a >> 1;
	}
	if (a<b) {
		b = (b - a) >> 1;
		return gcdcore(b, a);
	}
	else {
		a = (a - b) >> 1;
		return gcdcore(a, b);
	}
}
ll gcd(ll a, ll b) {
	if (!a && !b)
		return 0;
	if (a<0) return gcd(-a, b);
	if (b<0) return gcd(a, -b);
	ll c = 0;
	while (((a & 0x1) == 0) && ((b & 0x1) == 0)) {
		a = a >> 1;
		b = b >> 1;
		++c;
	}
	if ((a & 0x1) == 0) {
		a = a >> 1;
		return gcdcore(a, b) << c;
	}
	else {
		return gcdcore(b, a) << c;
	}
}
inline ll mul_inv(ll a, ll b)// returns x where (a * x) % b == 1
{
	ll b0 = b, t, q;
	ll x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
typedef std::pair<ll, ll> PLL;
PLL linear(std::vector<ll> A, std::vector<ll> B, std::vector<ll> M) //return x where A[i]*x = B[i] (mod M[i]) 
{
	ll x = 0, m = 1;
	register size_t i;
	for (i = 0; i < A.size(); i++) {
		ll a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
		if (b % d != 0)  
			return PLL(0, -1);//there are no possible values
		ll t = b / d * mul_inv(a / d, M[i] / d) % (M[i] / d);
		x = x + m*t;
		m *= M[i] / d;
	}
	x = (x % m + m) % m;
	return PLL(x, m);//m is lcm
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
	ll n;
	while (std::cin>>n) {
		std::vector<ll> a(n, 1);
		std::vector<ll> m(n);
		std::vector<ll> b(n);
		register size_t i;
		for (i = 0; i < n; ++i) {
			std::cin>>m[i]>>b[i];
		}
		PLL ans = linear(a, b, m);
		if (ans.second == -1)
			std::cout << -1 << std::endl;
		else 
			std::cout << ans.first << std::endl;
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