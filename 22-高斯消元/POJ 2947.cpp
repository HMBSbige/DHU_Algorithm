#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;

#define mem0(a) memset(a,0,sizeof(a))

const int MAXN = 310;
string str[]= { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };

int findNum(string s)
{
	for (int i = 0; i < 7; ++i)
	{
		if (str[i]==s) 
			return i;
	}
	return 0;
}
typedef int ll;
//stein算法
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
ll LCM(const ll& a, const ll& b)//最小公倍数
{
	return a / gcd(a, b) *b;
}
inline ll exgcd(ll m, ll n, ll &x, ll &y)
{
	ll x0 = 1, y0 = 0, x1 = 0, y1 = 1;
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

int n, m, k, cnt[MAXN];
int var, equ, a[MAXN][MAXN], ans[MAXN];
int gauss()
{
	int x, y;
	int k, col = 0;
	for (k = 0; k < equ && col < var; ++k, ++col)
	{
		int Max = 0, row = -1;
		for (int r = k; r < equ; ++r)
		{
			if (Max < abs(a[r][col]))
				Max = abs(a[r][col]), row = r;
		}
		if (row == -1)
		{
			--k;
			continue;
		}
		for (int c = col; c <= var; ++c)
			swap(a[k][c], a[row][c]);
		for (int r = k + 1; r < equ; ++r)
		{
			if (a[r][col])
			{
				int lcm = LCM(abs(a[k][col]), abs(a[r][col]));
				int ta = lcm / a[r][col];
				int tb = lcm / a[k][col];
				if (a[r][col] * a[k][col] < 0) tb = -tb;
				for (int c = col; c <= var; ++c)
				{
					a[r][c] = a[r][c] * ta - a[k][c] * tb;
					a[r][c] = (a[r][c] % 7 + 7) % 7;
				}
			}
		}
	}
	for (int r = k; r < equ; ++r)
	{
		if (a[r][var]) return -1;
	}
	if (k < var) 
		return 1;
	for (int r = var - 1; r >= 0; --r)
	{
		int tmp = a[r][var];
		for (int c = var - 1; c > r; --c)
		{
			tmp -= ans[c] * a[r][c] % 7;
		}
		tmp = (tmp % 7 + 7) % 7;
		exgcd(a[r][r], 7, x, y);
		ans[r] = (tmp * x % 7 + 7) % 7;
		if (ans[r] < 3) ans[r] += 7;
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false);
	while (cin>>n>>m && (n || m))
	{
		int x;
		string st, ed;
		mem0(a);
		var = n;
		equ = m;
		for (int i = 0; i < m; ++i)
		{
			mem0(cnt);
			cin >> k >> st >> ed;
			for (int j = 0; j < k; ++j)
			{
				cin >> x;
				++cnt[x - 1] ;
			}
			a[i][var] = findNum(ed) - findNum(st) + 1;
			for (int j = 0; j < var; ++j)
				a[i][j] = cnt[j] % 7;
		}

		int free_num = gauss();
		if (free_num == -1)
			cout << "Inconsistent data." << endl;
		else if (free_num == 1)
			cout << "Multiple solutions." << endl;
		else
			for (int i = 0; i < var; ++i)
				cout << ans[i] << (i == var - 1 ? '\n' : ' ');
	}
	return 0;
}