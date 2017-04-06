#include <iostream> 
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
//#include "bignumber\bigInt.h"
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
typedef int64_t ll;
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll r = ex_gcd(b, a%b, y, x);
	y -= x*(a / b);
	return r;
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
	ll a, b, r, x, y;
	while (std::cin >> a >> b) {
		r = ex_gcd(a, b, x, y);
		std::cout << x << " " << y << " " << r << std::endl;
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