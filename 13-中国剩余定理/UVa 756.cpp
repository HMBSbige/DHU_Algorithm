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
typedef uint64_t ull;
typedef int64_t ll;
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
ull chinese_remainder(std::vector<ull> n, std::vector<ull> a)//x=a[i](mod n[i])
{
	ull p, prod = 1, sum = 0;
	register size_t i;
	for (i = 0; i < n.size(); ++i) prod *= n[i];

	for (i = 0; i < n.size(); ++i) {
		p = prod / n[i];
		sum += a[i] * mul_inv(p, n[i]) * p;
		sum %= prod;
	}
	return (sum + prod) % prod;
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
	ll d;
	ull T=0;
	std::vector<ull> n(3);
	std::vector<ull> m = {23,28,33};
	while (std::cin >> n[0] >> n[1] >> n[2] >> d && !(n[0] == -1 && n[1] == -1 && n[2] == -1 && d == -1)) {
		ll ans = chinese_remainder(m, n) - d;
		ans = (ans% 21252 + 21252) % 21252;
		if (ans == 0)
			ans = 21252;
		std::cout << "Case " << ++T << ": the next triple peak occurs in " << ans << " days." << std::endl;

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