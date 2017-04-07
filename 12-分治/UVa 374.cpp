#include <iostream>
using namespace std;
typedef int64_t ll;
ll mult_mod(ll  a, ll   b, ll   c)
{
	a %= c;
	b %= c;
	ll ret = 0;
	ll tmp = a;
	while (b)
	{
		if (b & 1)
		{
			ret += tmp;
			if (ret > c)
				ret -= c;
		}
		tmp <<= 1;
		if (tmp > c)
			tmp -= c;
		b >>= 1;
	}
	return ret;
}
ll pow_mod(ll base, ll exp, ll modulus) {
  base %= modulus;
  ll result = 1;
  while (exp > 0) {
    if (exp & 1) result = mult_mod(result , base , modulus);
    base = mult_mod(base , base , modulus);
    exp >>= 1;
  }
  return result;
}
int main()
{
    std::ios::sync_with_stdio(false);
    ll b,p,m;
    while(cin>>b>>p>>m){
        cout<<pow_mod(b,p,m)<<endl;
    }
    return 0;
}