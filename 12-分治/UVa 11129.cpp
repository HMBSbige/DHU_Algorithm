#include <iostream> 
#include <vector>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
typedef uint64_t ll;
std::vector<ll> s;
std::vector<ll> temp;
void solve(ll n,ll l, ll r) {
	register size_t i;
	if (r - l < 2)
		return;
	ll k = l;
	for (int i = l; i <= r; i += 2)
		temp[k++] = s[i];
	for (int i = l + 1; i <= r; i += 2)
		temp[k++] = s[i];
	for (i = l; i <= r; ++i)
		s[i] = temp[i];
	ll mid = (l + r) >> 1;
	solve(n,l, mid);
	solve(n,mid, r);
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
	register size_t i;
	while (std::cin >> n && n) {
		std::vector<ll>(n).swap(s);
		std::vector<ll>(n).swap(temp);
		for (i = 0; i < n; ++i)
			s[i] = i;
		solve(n,0, n - 1);
		std::cout << n<<":";
		for (i = 0; i < n; ++i)
			std::cout<<" "<<s[i];
		std::cout << std::endl;
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