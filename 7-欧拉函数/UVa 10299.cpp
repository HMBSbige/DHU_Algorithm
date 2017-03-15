#include <iostream>
#include <new>

using namespace std;
typedef uintmax_t ull;

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
			n = n/i*(i - 1);
			while (a%i == 0) a /= i;
		}
	}
	if (a>1) n = n / a*(a - 1);
	return n;
}
ull* Euler::MakeEuler(ull N)
{
	ull *phi = new ull[N + 1];
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
int main() {
	ios::sync_with_stdio(false);
	int n;
	Euler e;
	while (cin >> n && n) {
		if (n == 1)
			cout << 0 << endl;
		else
			cout << e._Euler(n) << endl;
	}
	//system("pause");
	return 0;
}