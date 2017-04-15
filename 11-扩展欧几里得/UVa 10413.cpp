#include <iostream> 
#include <vector>
#include <algorithm>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
typedef int64_t ll;
ll exgcd(ll m, ll n, ll &x, ll &y)
{
	ll x1, y1, x0, y0;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	ll r = m%n;
	ll q = (m - r) / n;
	while (r)
	{
		x = x0 - q*x1; y = y0 - q*y1;
		x0 = x1; y0 = y1;
		x1 = x; y1 = y;
		m = n; n = r; r = m%n;
		q = (m - r) / n;
	}
	return n;
}
bool isMeet(ll m,ll n,std::vector<ll> C, std::vector<ll> P, std::vector<ll> L) {
	// c[i] + k * p[i] = a * m  --- (1)
	// c[j] + k * p[j] = b * m  --- (2)
	// (c[i] - c[j]) + k * (p[i] - p[j]) = m * (a - b)
	// k * (p[j] - p[i])+(a - b) * m = c[i] - c[j]
	register size_t i,j;
	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			ll a = P[j] - P[i], b = m, c = C[i] - C[j];
			if (a < 0) {
				a = -a;
				c = -c;
			}
			ll x, y, g;
			g=exgcd(a, b, x, y);

			if (c%g)
				continue;
			x *= (c / g);
			x = (x % (b / g) + b / g) % (b / g);
			if (x <= std::min(L[i], L[j]))
				return true;
		}
	}
	return false;
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
	ll t,n,m;
	register size_t i;
	std::vector<ll> C, P, L;
	std::cin >> t;
	while (t--) {
		std::cin >> n;
		std::vector<ll>(n).swap(C);
		std::vector<ll>(n).swap(P);
		std::vector<ll>(n).swap(L);
		for (i = 0; i < n; ++i)
			std::cin >> C[i] >> P[i] >> L[i];
		m=*max_element(C.begin(), C.end());
		for (i = m; i <=1000000; ++i)
			if (!isMeet(i,n,C,P,L))
				break;
		std::cout << i << std::endl;
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