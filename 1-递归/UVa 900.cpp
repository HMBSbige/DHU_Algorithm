#include <iostream>
#include <cmath>
using namespace std;

int c(int m, int n)
{
	int i, j, sum = 1;
	for (i = m, j = 0; j<n; j++, i--)
	{
		sum = sum*i / (j + 1);
	}
	return sum;
}

int main() {
	int n;
	while (cin >> n && n > 0) {
		int a = 0,b=n,ans=0;
		do {
			ans += c(b, a);
			++a;
			b = n - 2 * a + a;
		} while (a <= b);
		cout << ans << endl;
		
	}
	return 0;
}