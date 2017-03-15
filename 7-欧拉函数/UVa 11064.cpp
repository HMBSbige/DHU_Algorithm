#include <iostream>
#include <vector>
#include <set>
#include <new>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef uintmax_t ull;

class Primes
{
private:
	set<ull> Prime;
	bool *isPrime= NULL;
	ull *vecPrime= NULL;
	void release();
public:
	Primes(ull);
	~Primes();
	void MakePrime(ull);//膜改筛法素数生成器
	ull Number();//返回生成的素数个数
	ull Number(ull n);//返回<=n的素数的个数
	ull at(ull n);//返回第n个素数，错误返回0
	bool isPrimeNumer(ull);//判断是否是素数
	ull find(ull);//返回n是第几个素数，错误返回0
	vector<pair<ull, ull> >factor(ull n);//将n分解质因数
	ull Euler(ull n);//返回欧拉函数
};
Primes::Primes(ull N) {
	N = min((ull)Prime.max_size(), N);
	MakePrime(N);
}
Primes::~Primes(){
	release();
}
void Primes::MakePrime(ull N)//膜改快速线性筛法
{
	release();
	ull m = N;
	--N;
	N /= 2;
	ull sn = (ull)(sqrt(2 * N) / 2);
	vector<bool> p(N, 1);
	for (ull i = 0; i < sn; i++) {
		if (p[i])
		{
			for (ull j = i*(2 * i + 6) + 3; j<N; j += 2 * i + 3)
				p[j] = false;
		}
	}
	set<ull>().swap(Prime);
	isPrime = new bool[m + 1];
	memset(isPrime, 0, sizeof(bool)*(m+1));
	Prime.insert(2);
	isPrime[2] = true;
	for (ull i = 0; i<N; ++i) {
		if (p[i]) {
			Prime.insert(i + i + 3);
			isPrime[i + i + 3] = true;
		}
	}
	vecPrime = new ull[Prime.size()];
	vecPrime[0]=2;
	for (ull i = 0,j=0; i<N; ++i) {
		if (p[i]) {
			vecPrime[++j] = i + i + 3;
		}
	}
	return;
}

void Primes::release(){
	if (isPrime != NULL)
		delete[] isPrime;
	if (vecPrime != NULL)
		delete[] vecPrime;
}
ull Primes::Number()
{
	return Prime.size();
}

ull Primes::at(ull n)
{
	if (n < Number() && n>0)
		return vecPrime[n-1];
	else
		return 0;
}
ull Primes::Number(ull n)
{
	/*auto it = Prime.begin();
	advance(it, n);*/
	return distance(Prime.begin(), Prime.upper_bound(n));;
}
bool Primes::isPrimeNumer(ull num)
{
	set<ull>::iterator it=Prime.find(num);
	if (it == Prime.end())
		return false;
	return true;
}
ull Primes::find(ull num)
{
	set<ull>::iterator it = Prime.find(num);
	if (it == Prime.end())
		return 0;
	return distance(Prime.begin(), Prime.upper_bound(num));
}
vector<pair<ull, ull>> Primes::factor(ull n)
{
	ull temp, i, now;
	vector<pair<ull, ull>> a;
	temp = Number((ull)(sqrt(n)));
	now = n;
	for (i = 0; now > 1 && i < temp; ++i)
		if (now%vecPrime[i] == 0) {
			a.push_back(make_pair(vecPrime[i], 0));
			while (now%vecPrime[i] == 0) {
				++get<1>(*(a.end() - 1));
				now /= vecPrime[i];
			}
		}
	if (now != 1)
		a.push_back(make_pair(now, 1));
	return a;
}
ull Primes::Euler(ull n)
{
	if (n == 1)
		return 1;
	vector<pair<ull, ull> > f = factor(n);
	for (size_t i = 0; i < f.size(); ++i)
		n = n / f[i].first * (f[i].first - 1);
	return n;
}
int main()
{
    ios::sync_with_stdio(false);
    Primes p((ull)(sqrt(1ULL<<32)));
    ull n;
    vector<pair<ull, ull> > f;
    ull t;
    while(cin>>n){
        f=p.factor(n);
        t=1;
        for(size_t i=0;i<f.size();++i)
            t*=f[i].second+1;
        cout<<n-p.Euler(n)-t+1<<endl;//
    }
    return 0;
}
