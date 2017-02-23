#include <iostream>
#include <cmath>
#define uLL unsigned long long
using namespace std;

uLL male(int n)
{
	uLL result_2;
	uLL result_1 = 1, result = 2;
	if (n <= 2)
		return n;
	while (n > 2) {
		n -= 1;
		result_2 = result_1;
		result_1 = result;
		result = result_1 + result_2+1;
	}
	return result;
}
int main() {
	int n;
	while (cin >> n && n >= 0) {
		cout << male(n) <<" "<<male(n+1) << endl;
	}
	return 0;
}