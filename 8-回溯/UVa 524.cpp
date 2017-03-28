#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;
//#define DEBUG
#ifdef DEBUG
#include <fstream>
ofstream outfile;
#endif // DEBUG
/////////////////////////////////////////////////
using ull = int;
bool isPrime[] = {0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0};
int n;
int circle[20];
bool used[20];
void search(int m) {
	if (m == n - 1 && isPrime[circle[n - 1] + circle[n]]) {
		for (int i = 0; i < n; i++) {
			cout << circle[i];
			if (i != n - 1)
				cout << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 2; i <= n; i++) {
		if (!used[i] && isPrime[circle[m] + i]) {
			used[i] = true;
			circle[m + 1] = i;
			search(m + 1);
			used[i] = false;
		}
	}

		
}

int main()
{
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef DEBUG
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", ios::trunc);
#endif // DEBUG
	///////////////////////////////////
	int  T = 0;
	while (cin>>n) {
		if (T > 0) 
			cout <<endl;
		cout <<"Case "<<++T<<":"<<endl;
		circle[0] = circle[n] = 1;
		search(0);
	}
	///////////////////////////////////
#ifdef DEBUG
	outfile.close();
	system("pause");
#endif // DEBUG
	return 0;
}