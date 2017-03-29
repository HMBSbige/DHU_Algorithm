#include <iostream>
#include <new>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef uintmax_t ull;
#define maxn 100000

class Euler {
private:

public:
	ull _Euler(ull n);
	ull* MakeEuler(ull N);
};
ull Euler::_Euler(ull n)
{
	ull a = n;
	for (int i = 2; i*i <= a; i++) {
		if (a%i == 0) {
			n = n / i*(i - 1);
			while (a%i == 0) a /= i;
		}
	}
	if (a>1) n = n / a*(a - 1);
	return n;
}
ull* Euler::MakeEuler(ull N)
{
	ull *phi=new ull[N+1];
	int i, j;
	for (i = 1; i <= N; i++)
		phi[i] = i;
	for (i = 2; i <= N; i += 2)
		phi[i] /= 2;
	for (i = 3; i <= N; i += 2)
		if (phi[i] == i) {
			for (j = i; j <= N; j += i)
				phi[j] = phi[j] / i * (i - 1);
		}
	return phi;
}
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
	vector<ull> minfactor(ull n);//返回2-n的最小素因数
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
vector<pair<ull, ull> > Primes::factor(ull n)
{
	ull temp, i, now;
	vector<pair<ull, ull> > a;
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
vector<ull> Primes::minfactor(ull n) {
	vector<ull> m(n + 1, 0);
	for (ull i = 2; i <= n; ++i)
	{
		if (isPrimeNumer(i))
			m[i] = i;
		else {
			for (ull j = 0; j < Number(); ++j) {
				if (i%vecPrime[j] == 0) {
					m[i] = vecPrime[j];
					break;
				}
				m[i] = i;
			}

		}
	}
	return m;
}
ull gcd(ull a, ull b) {
	return b == 0 ? a : gcd(b, a%b);
}
Primes p(maxn);
ull fff(ull n,ull m)//n < m,求1-n内和m互质的数的个数
{
    vector<pair<ull, ull> > f=p.factor(m);
    ull ans = 0;//不互质的个数
    ull cnt,temp;
    for(int i = 1;i < (1<<f.size());i++)
    {
        cnt = 0;
        temp = 1;
        for(int j = 0;j < f.size();j++)
            if(i&(1<<j))//判断第几个因子目前被用到
            {
                cnt++;
                temp *= f[j].first;
            }
        if(cnt&1)//奇数
            ans += n/temp;
        else
            ans -= n/temp;
    }
    return n - ans;
}
int main()
{
    ios::sync_with_stdio(false);
    ull N,T=0;
    ull a, b, c, d, k;
    ull ans;
    Euler e;
    register ull i;
    ull *phi=e.MakeEuler(maxn);
    cin>>N;
    while(N--){
        cin>>a>>b>>c>>d>>k;//a=c=1
        if(k==0){
            cout<<"Case "<<++T<<": "<<0<<endl;
            continue;
        }
        //
        b/=k;d/=k;
        if(b>d)
            swap(b,d);
        //
        ans=0;
        for(i=1;i<=b;++i)
            ans+=phi[i];
        //
        for(i=b+1;i<=d;++i)
            ans+=fff(b,i);//减去不互质
        cout<<"Case "<<++T<<": "<<ans<<endl;
    }
    return 0;
}/*
5
1 3 1 5 1
1 11014 1 14409 9
*/
