#include <iostream> 
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
void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d) {
	if (!b) { d = a, x = 1, y = 0; }
	else {
		ex_gcd(b, a % b, y, x, d);
		y -= x * (a / b);
}
}
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
ll china_remain(std::vector<ull> m, std::vector<ull> r)
{
	ll a, b, c, c1, c2, x, y, d;
	a = m[0]; c1 = r[0];
	for (int i = 1; i<m.size(); i++)
	{
		b = m[i]; c2 = r[i];
		ex_gcd(a, b,  x, y,d);
		c = c2 - c1;
		if (c%d)
			return -1;
		ll b1 = b / d;
		x = ((c / d*x) % b1 + b1) % b1;
		c1 = a*x + c1;
		a = a*b1;
	}
	if (c1 == 0)//当余数都为0  
	{
		c1 = 1;
		for (int i = 0; i<m.size(); i++)
			c1 = c1*m[i] / gcd(c1, m[i]);
	}
	return c1;
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
	ll T,t=0;
	size_t n;
	register size_t i;
	std::vector<ull> m;
	std::vector<ull> r;
	std::cin >> T;
	while(T--)
	{
		std::cin >>n;
		std::vector<ull>(n).swap(m);
		std::vector<ull>(n).swap(r);
		for (i = 0; i < n; ++i)
			std::cin >> m[i];
		for (i = 0; i < n; ++i)
			std::cin >> r[i];
		std::cout << "Case " << ++t << ": " << china_remain(m,r) << std::endl;
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