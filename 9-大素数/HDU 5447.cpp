#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>

typedef uint64_t ull;
typedef int64_t ll;
using namespace std;
string ToString(const ull& t)//数字转字符串
{
	ostringstream oss;
	oss << t;
	return oss.str();
}
inline int64_t double2int64(double d)//d<1125899906842623
{
	d += 6755399441055744.0;// 1.5 * 2^52
	int64_t i = reinterpret_cast<int64_t&>(d);
	i <<= 13;
	i >>= 13;
	return i;
}
vector<string> ss = { "18446744073709551616","36893488147419103232","73786976294838206464","147573952589676412928","295147905179352825856","590295810358705651712","1180591620717411303424","2361183241434822606848","4722366482869645213696","9444732965739290427392","18889465931478580854784","37778931862957161709568","75557863725914323419136","151115727451828646838272","302231454903657293676544","604462909807314587353088","1208925819614629174706176","2417851639229258349412352","4835703278458516698824704","9671406556917033397649408","19342813113834066795298816","38685626227668133590597632","77371252455336267181195264","154742504910672534362390528","309485009821345068724781056","618970019642690137449562112","1237940039285380274899124224","2475880078570760549798248448","4951760157141521099596496896","9903520314283042199192993792","19807040628566084398385987584","39614081257132168796771975168","79228162514264337593543950336","158456325028528675187087900672","316912650057057350374175801344","633825300114114700748351602688","1267650600228229401496703205376","2535301200456458802993406410752","5070602400912917605986812821504","10141204801825835211973625643008","20282409603651670423947251286016","40564819207303340847894502572032","81129638414606681695789005144064","162259276829213363391578010288128","324518553658426726783156020576256","649037107316853453566312041152512","1298074214633706907132624082305024","2596148429267413814265248164610048","5192296858534827628530496329220096","10384593717069655257060992658440192","20769187434139310514121985316880384","41538374868278621028243970633760768","83076749736557242056487941267521536","166153499473114484112975882535043072","332306998946228968225951765070086144","664613997892457936451903530140172288","1329227995784915872903807060280344576","2658455991569831745807614120560689152","5316911983139663491615228241121378304","10633823966279326983230456482242756608","21267647932558653966460912964485513216","42535295865117307932921825928971026432","85070591730234615865843651857942052864","170141183460469231731687303715884105728" };

class uint128_t {
private:
std::string add(std::string a, std::string b)
{
	register size_t i, j;
	char x, y, z;
	std::string c;
	int up = 0;
	for (i = 0, j = 0; i <= a.size() - 1 || j <= b.size() - 1; ++i, ++j)
	{
		if (i>a.size() - 1)
			x = '0';
		else
			x = a[a.size() - 1 - i];
		if (j>b.size() - 1)
			y = '0';
		else
			y = b[b.size() - 1 - j];
		z = x - '0' + y - '0';
		if (up)
			z += 1;
		if (z>9) {
			up = 1;
			z %= 10;
		}
		else
			up = 0;
		c.push_back(z + '0');
	}
	if (up)
		c.push_back('1');
	reverse(c.begin(), c.end());
	return c;
}
std::string mult(std::string a, std::string b)
{

	register size_t i, j;
	size_t alen = a.size(), blen = b.size();
	size_t maxn = alen + blen - 1;
	int sum = 0;
	std::vector<std::vector<int> > res(maxn, std::vector<int>(blen, 0));
	std::string result;

	for (i = 0; i<alen; i++)
		for (j = 0; j<blen; j++)
			res[i][j] = (a[i] - '0')*(b[j] - '0');

	for (i = 0; i <= alen - 1; ++i)
	{
		for (j = 0; j <= blen - 1; ++j)
			sum = sum + res[alen - 1 - i + j][blen - 1 - j];
		result.push_back(sum % 10);
		sum = sum / 10;
	}

	if (blen >= 2)
		for (i = 0; i <= blen - 2; ++i)
		{
			for (j = 0; j <= blen - 2 - i; ++j)
				sum = sum + res[blen - 2 - i - j][j];
			result.push_back(sum % 10);
			sum = sum / 10;
		}

	if (sum != 0)
		result.push_back(sum);

	for (i = 0; i<result.size(); ++i)
		result[i] += '0';
	reverse(result.begin(), result.end());

	while (1)
	{
		if (result.size() != a.size() && result[0] == '0')
			result.erase(result.begin());
		else
			break;
	}
	return result;
}
inline ull M(ull x, ull MOD) { while (x >= MOD)x -= MOD; return x; }
inline ull cheng(ull a, ull b, ull p) {
	ull mmh = 0;
	while (b) {
		if (b & 1) mmh = M(mmh + a, p);
		a = M(a + a, p); b >>= 1;
	}
	return mmh;
}
char P_C[50], O_O[50];
string c;//2^128-1
inline bool ju(size_t i) {
	size_t cl = c.size(), sl = ss[i].size();
	if (cl<sl)
		return false;
	else if (cl == sl)
		for (register size_t j = 0; j<cl; ++j)
			if (c[j]<ss[i][j])
				return false;
			else if (c[j]>ss[i][j])
				break;
	for (register size_t j = 0; j<cl - sl; ++j)
		c[j] -= 48;
	for (register size_t j = 0; j<sl; ++j)
		c[cl - j - 1] -= ss[i][sl - j - 1];
	for (register size_t j = 0; j<cl; ++j)
		for (register size_t j = cl - 1; j; --j)
			if (c[j]<0)
				c[j] += 10, c[j - 1]--;
	for (i = 0; c[i] == 0 && i<cl; ++i);
	if (i == cl)
		c[0] = '0', c.resize(1);
	else
		for (register size_t j = i; j <= cl; ++j)
			c[j - i] = c[j] + 48;
	c.resize(cl - i);
	return true;
}
inline ull change() {
	size_t cl = c.size();
	ull x = 0;
	for (register int i = 0; i<cl; i++)
		x *= 10, x += c[i] - 48;
	return x;
}
inline void add(int x) {
	int i;
	size_t cl = strlen(P_C), sl = ss[x].size();
	for (i = 0; i<sl; i++) O_O[i] = ss[x][sl - i - 1] - 48;
	for (i = 0; i<cl; i++) O_O[cl - i - 1] += P_C[i] - 48;
	if (sl>cl) cl = sl;
	for (i = 0; i<cl; i++)
		if (O_O[i] >= 10) O_O[i + 1] += O_O[i] / 10, O_O[i] %= 10, cl += i == (cl - 1);
	for (i = 0; i<cl; i++) P_C[i] = O_O[cl - i - 1] + 48; P_C[cl] = 0;
}
public:
	ull a, b;
	uint128_t(ull _a = 0, ull _b = 0) :a(_a), b(_b) {}
	void pr() {
		ull A = a, B = b; int s = 0;
		memset(P_C, 0, sizeof(P_C));
		memset(O_O, 0, sizeof(O_O));
		while (B) O_O[s++] = B % 10 + 48, B /= 10; P_C[s] = 0;
		for (register int i = 0; i<s; i++) P_C[i] = O_O[s - i - 1];
		for (register int i = 0; i <= 35; i++)
			if (A&(1ull << i)) add(i);
		cout << P_C << " ";
	}
	uint128_t operator >>=(const ull &y);
	uint128_t operator <<=(const ull &y);
	uint128_t operator >>(const ull &y);
	uint128_t operator <<(const ull &y);
	uint128_t operator +(const uint128_t &y);
	uint128_t operator +(const ll &y);
	uint128_t operator -(const uint128_t &y);
	uint128_t operator -(const ll &y) ;
	uint128_t operator *(const uint128_t &y);
	bool operator <(const uint128_t &y);
	bool operator >(const uint128_t &y);
	bool operator !=(const uint128_t &y);
	bool operator ==(const uint128_t &y);
	uint128_t operator %(const uint128_t &y);
	uint128_t operator /(const uint128_t &y);
	ull operator %(const int &y) ;
	ull operator %(const ull &y);
	friend std::istream& operator>>(std::istream& is, uint128_t& n);
	friend std::ostream& operator<<(std::ostream& is, uint128_t& value) ;
};
uint128_t uint128_t::operator >>=(const ull &y){
    ull i=y;
    while(i--){
        this->b >>= 1;
        if (this->a & 1) this->b |= 1ull << 63;
        this->a >>= 1;
    }
    return *this;
}
uint128_t uint128_t::operator <<=(const ull &y){
    ull i=y;
    while(i--){
       this->a <<= 1;
       if (this->b&(1ull << 63)) this->a |= 1;
       this->b <<= 1;
    }
    return *this;
}
uint128_t uint128_t::operator >>(const ull &y){
    uint128_t tmp=*this;
    ull i=y;
    while(i--){
        tmp.b >>= 1;
        if (tmp.a & 1) tmp.b |= 1ull << 63;
        tmp.a >>= 1;
    }
    return tmp;
}
uint128_t uint128_t::operator <<(const ull &y){
    uint128_t tmp=*this;
    ull i=y;
    while(i--){
       tmp.a <<= 1;
       if (tmp.b&(1ull << 63)) tmp.a |= 1;
       tmp.b <<= 1;
    }
    return tmp;
}
uint128_t uint128_t::operator +(const uint128_t &y) {
	uint128_t z;
	z.a = this->a + y.a;
	z.b = this->b + y.b;
	if (z.b<this->b || z.b<y.b)
        ++z.a;
	return z;
}
uint128_t uint128_t::operator +(const ll &y) {
	uint128_t z = *this;
	if ((z.b + y)<z.b)
        ++z.a;
    z.b += y;
	return z;
}
uint128_t uint128_t::operator -(const uint128_t &y) {
	uint128_t z;
	z.a = this->a - y.a;
	z.b = this->b - y.b;
	 if (y.b>this->b)
        --z.a;
	return z;
}
uint128_t uint128_t::operator -(const ll &y) {
	uint128_t z = *this;
	if (z.b<y) z.a--; z.b -= y;
	return z;
}
uint128_t uint128_t::operator *(const uint128_t &y) {
	if (this->a) {
		uint128_t z = *this, mmh = uint128_t(0, 0), u = y;
		while (u.a | u.b) {
			if (u.b & 1) mmh = mmh + z;
			z<<=1; u>>=1;
		}
		return mmh;
	}
	ull s = (1ull << 32) - 1;
	ull a = (this->b >> 32)*(y.b >> 32), _b1 = (this->b&s)*(y.b >> 32), b = _b1 + (this->b >> 32)*(y.b&s), c = (this->b&s)*(y.b&s), d;
	a += (b<_b1) * 1ull << 32;
	d = c + ((b&s) << 32); a += d<c; a += b >> 32;
	return uint128_t(a, d);
}
bool uint128_t::operator <(const uint128_t &y) { return this->a == y.a ? this->b<y.b : this->a<y.a; }
bool uint128_t::operator >(const uint128_t &y) { return this->a == y.a ? this->b>y.b : this->a>y.a; }
bool uint128_t::operator !=(const uint128_t &y) { return !(*this==y); }
bool uint128_t::operator ==(const uint128_t &y) { return this->a == y.a&&this->b == y.b; }
uint128_t uint128_t::operator %(const uint128_t &y) {
	if (*this<y)
        return *this;
	uint128_t z = y, c = *this;
	while (!(z>c)) z<<=1;
	for (;;) {
		z>>=1;
		if (!(c<z))c = c - z;
		if (z.a == y.a&&z.b == y.b) break;
	}
	return c;
}
uint128_t uint128_t::operator /(const uint128_t &y) {
	if (*this<y) return uint128_t{ 0,0 };
	uint128_t z = y, c = *this, a = uint128_t{ 0,0 };
	while (!(z>*this)) z<<=1;
	for (;;) {
		z>>=1; a<<=1;
		if (!(c<z))c = c - z, a.b |= 1;
		if (z.a == y.a&&z.b == y.b) break;
	}
	return a;
}
ull uint128_t::operator %(const int &y) {
	uint128_t z = *this;
	z.a %= y; z.b %= y;
	z.a <<= 32; z.a %= y;
	z.a <<= 32; z.a %= y;

	z.b += z.a; if (z.b >= y) z.b -= y;
	return z.b;
}
ull uint128_t::operator %(const ull &y) {
	uint128_t z = *this;
	z.a %= y; z.b %= y;
	for (int i = 0; i<64; i++) z.a <<= 1, z.a %= y;

	z.b += z.a; if (z.b >= y) z.b -= y;
	return z.b;
}
ull sqrt(uint128_t x) {
	ull l = 0, r = double2int64(1e18), _mid;
	uint128_t mid;
	while (l<r) {
		mid.a = 0; mid.b = _mid = (l + r) >> 1;
		mid = mid*mid;
		if (x == mid) return _mid; else if (x<mid) r = _mid - 1; else if (x>mid) l = _mid + 1;
	}
	return l;
}
ull sqrt3(uint128_t x) {
	ull l = 0, r = double2int64(1e12), _mid;
	uint128_t mid = uint128_t(0, 0);
	while (l<r) {
		mid.a = 0; mid.b = _mid = (l + r) >> 1;
		mid = mid*mid*mid;
		if (x == mid) return _mid; else if (x<mid) r = _mid - 1; else if (x>mid) l = _mid + 1;
	}
	return l;
}
std::istream& operator>>(std::istream& is, uint128_t& n) {
	is >> n.c;
	n.a = n.b = 0;
	for (size_t i = ss.size() - 1; i > 0; i--) {
		n.a <<= 1;
		if (n.ju(i))
			n.a |= 1;
	}
	n.a <<= 1;
		if (n.ju(0))
			n.a |= 1;
	n.b = n.change();
	return is;
}
std::ostream& operator<<(std::ostream& is, uint128_t& value) {
	is << value.add(value.mult(ToString(value.a), ss[0]), ToString(value.b));
	return is;
}
const int S = 20;
const ull m_p[20] = { 2,5,7,61,97,37,101,13,11,997,2083,5807,7213,9907,10781,11897,14033,18013,43789,10009 };
uint128_t cheng(uint128_t a, uint128_t b, uint128_t p) {
	uint128_t mmh; mmh = uint128_t{ 0,0 };
	while (b.a || b.b) {
		if (b.b & 1) if (mmh = mmh + a, !(mmh<p)) mmh = mmh - p;
		b>>=1; a = a + a; if (!(a<p)) a = a - p;
	}
	return mmh;
}
uint128_t mi(uint128_t a, uint128_t b, uint128_t p) {
	uint128_t mmh; mmh = { 0,1 };
	while (b.a || b.b) {
		if (b.b & 1ull) mmh = cheng(mmh, a, p);
		b>>=1; a = cheng(a, a, p);
	}
	return mmh;
}
bool prime_judge(uint128_t n) {
	if (n.b == 2 && n.a == 0) return 1;
	if ((n.b<2 && n.a == 0) || !(n.b & 1)) return 0;
	for (register int i = 0; i<S; i++)
		if (m_p[i] == n.b&&n.a == 0)
			return 1;
		else if (mi(uint128_t{ 0,(n.a ? m_p[i] : m_p[i] % n.b) }, n - 1, n) != uint128_t{ 0,1 })
			return 0;
	return 1;
}
uint128_t gcd(uint128_t x, uint128_t y) { return (y.a == 0 && y.b == 0) ? x : gcd(y, x%y); }
uint128_t k1, k2, u;
#define MN 1000001
bool bo[MN];
ull mmh1, mmh2, T, p[MN], num = 0, A;
inline void work(uint128_t k, ull &mmh, uint128_t u) {
	if (u.a) return;
	ull s = u.b;
	if (s<1e8&&k == u*u*u) mmh *= 3; else
		if (k == u*u || (s <= 1e8&&k % (s*s) == 0)) mmh *= 2; else {
			if (k == u) return;
			k = k / u;
			u = uint128_t(0, sqrt(k));
			if (u*u == k) mmh <<= 1;
		}
}
int main() {
	std::ios::sync_with_stdio(false);
	register int i, j;
	for (i = 2; i<MN; i++) {
		if (!bo[i]) p[++num] = i;
		for (j = 1; j <= num&&i*p[j]<MN; j++)
			if (bo[i*p[j]] = 1, i%p[j] == 0) break;
	}
	cin >> T;
	while (T--) {
		cin >> k1;//340282366920938463463374607431768211455
		cin >> k2;//170141183460469231731687303715884105727//85070591730234615865843651857942052863
		mmh1 = mmh2 = 1;
		for (i = 1; i <= num; i++)
			if (k1%p[i] == 0) {
				A = 1; k1 = k1 / uint128_t(0, p[i]);
				while (k1%p[i] == 0)
					A++, k1 = k1 / uint128_t{ 0,p[i] };
				mmh1 = mmh1*A;
			}
		for (i = 1; i <= num; i++)
			if (k2%p[i] == 0) {
				A = 1; k2 = k2 / uint128_t{ 0,p[i] };
				while (k2%p[i] == 0) A++, k2 = k2 / uint128_t{ 0,p[i] };
				mmh2 = mmh2*A;
			}

		u = gcd(k1, k2);
		if (prime_judge(u)) work(k1, mmh1, u), work(k2, mmh2, u); else
			if (u != uint128_t(0, 1)) {
				if (A = sqrt(u), u == uint128_t(0, A)*uint128_t(0, A)) mmh1 *= (uint128_t(0, A)*u == k1) + 2, mmh2 *= (uint128_t(0, A)*u == k2) + 2; else
					if (A = sqrt3(u), u == uint128_t(0, A)*uint128_t(0, A)*uint128_t(0, A)) mmh1 *= 3, mmh2 *= 3;
			}
		cout << mmh1 << " " << mmh2 << endl;
	}
	return 0;
}
