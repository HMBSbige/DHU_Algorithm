#include <iostream> 
#include <cmath>
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
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef ofile	
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", std::ios::trunc);
	std::cout.rdbuf(outfile.rdbuf());
#endif
	//////////////////////////////////////////////////////////////////////
	ll n,c1,c2,n1,n2;
	while (std::cin>>n && n) {
		std::cin>>c1>>n1>>c2>>n2;
		ll  xi, yi, x, y;
		ll d=exgcd(n1, n2, xi, yi);
		ll lower = ceil(-1.0 * n * xi / n2);
		ll up = floor(1.0 * n * yi / n1);

		if (lower > up || n % d) {
			std::cout<<"failed"<<std::endl;
			continue;
		}

		if (c1 * n2 > c2 * n1) {
			x = xi * n / d + n2 / d * lower;
			y = yi * n / d - n1 / d * lower;
		}
		else {
			x = xi * n / d + n2 / d * up;
			y = yi * n / d - n1 / d * up;
		}
		std::cout << x<<" "<<y<< std::endl;
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