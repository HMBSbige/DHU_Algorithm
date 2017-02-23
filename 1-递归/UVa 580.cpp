#include <iostream>
#include <cmath>
#define uLL unsigned long long
using namespace std;
uLL _(int n)
{
	uLL result[5];
	result[1]=2;
	result[2]=4;
	result[3]=7;
	result[4]=13;
	if (n <=4)
		return result[n];
	while (n > 4) {
		n -= 1;
		result[1] = result[2];
		result[2] = result[3];
		result[3] = result[4];
		result[4] = result[1] + result[2] + result[3];
	}
	return result[4];
}
int main() {
	int n;
	while (cin >> n && n > 0) {
		cout <<(1<<n)-_(n) << endl;
	}
	return 0;
}