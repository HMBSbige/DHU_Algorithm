#include <iostream> 
#include <vector>
#include <set>
#include <algorithm>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
typedef uint64_t ull;
typedef int64_t ll;
size_t C, S;
std::vector<ll> X(1024, 0);
std::vector<ll> Xn(1024, 0);
std::vector<ll> a(1024, 0);
std::vector<std::vector<ll> > Y(1024, std::vector<ll>(128, 0));
std::vector<ll> solution;
inline ll inv(ll a, ll b)// returns x where (a * x) % b == 1
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
ll chinese_remainder(size_t n, std::vector<ll> m, std::vector<ll> a) {
	ll M = 1, ret = 0;
	register size_t i;
	for (i = 0; i < n; ++i)
		M *= m[i];
	for (i = 0; i < n; ++i) {
		ret += a[i] * inv(M / m[i], m[i]) % M * M / m[i];
		ret %= M;
	}
	return (ret%M + M) % M;
}
void dfs(ll idx) {
	register size_t i;
	if (idx == C) {
		ll smallest = chinese_remainder(C, X, a);
		solution.push_back(smallest);
		return;
	}
	for (i = 0; i < Xn[idx]; ++i) {
		a[idx] = Y[idx][i];
		dfs(idx + 1);
	}
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
	register size_t i,j,k,ratio;
	while (std::cin>>C>>S && C + S) {
		std::set<ll> remainder[1024];
		for (i = 0; i < C; ++i) {
			std::cin >> X[i]>>Xn[i];
			for (j = 0; j < Xn[i]; ++j) {
				std::cin >> Y[i][j];
				remainder[i].insert(Y[i][j]);
			}
			sort(Y[i].begin(), Y[i].begin() + Xn[i]);
		}
		std::vector<ll>().swap(solution);
		ll o = 1, M = 1;
		for (i = 0; i < C; ++i) {
			o *= Xn[i];
			M *= X[i];
		}
		if (o < 10000) {
			dfs(0);
			sort(solution.begin(), solution.end());
			for (i = 0, ratio = 0; i < S; ++ratio) {
				for (j = 0; j < solution.size() && i < S; ++j) {
					ll mn = solution[j] + ratio * M;
					if (mn == 0)
						continue;
					std::cout << mn << std::endl;
					++i;
				}
			}
		}
		else {
			size_t base = 0;
			for (i = 0; i < C; ++i)
				if (X[base] * Xn[i] < X[i] * Xn[base])
					base = i;
			for (i = 0, ratio = 0; i < S; ++ratio) {
				for (j = 0; j < Xn[base] && i < S; ++j) {
					ll mn = (ll)ratio * X[base] + Y[base][j];
					if (mn == 0) 
						continue;
					bool f = true;
					for (k = 0; k < C; ++k)
						f &= remainder[k].find(mn%X[k]) != remainder[k].end();
					if (f) {
						std::cout << mn << std::endl;
						++i;
					}
				}
			}
		}
		std::cout <<std::endl;
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