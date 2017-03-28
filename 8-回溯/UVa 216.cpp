#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
//#define DEBUG
using namespace std;
/////////////////////////////////////////////////
const int maxn = 10;

int p[maxn], rec[maxn], n;
double sum, x[maxn], y[maxn];

double dis(double ax, double ay, double bx, double by) {
	double dx, dy;
	dx = ax - bx;
	dy = ay - by;
	return sqrt(dx * dx + dy * dy) + 16;
}

void solve(void) {
	double tmp = 0;
	for (int i = 0; i < n - 1; i++)
		tmp += dis(x[p[i]], y[p[i]], x[p[i + 1]], y[p[i + 1]]);
	if (tmp < sum) {
		sum = tmp;
		for (int i = 0; i < n; i++)
			rec[i] = p[i];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
	///////////////////////////////////
	int cnt = 0;
	while (cin>>n && n) {
		for (int i = 0; i < n; i++) {
			cin>>x[i]>>y[i];
			p[i] = i;
		}
		sum = INT_MAX;
		do {
			solve();
		} while (next_permutation(p, p + n));
		cout<<"**********************************************************"<<endl;
		cout << "Network #" << ++cnt << endl;
		for (int i = 0; i < n - 1; i++)
			cout<<"Cable requirement to connect ("<< int(x[rec[i]])<<","<< int(y[rec[i]])<<") to ("<< int(x[rec[i + 1]])<<","<< int(y[rec[i + 1]])<<") is "<<setprecision(2) << setiosflags(ios::fixed) <<dis(x[rec[i]], y[rec[i]], x[rec[i + 1]], y[rec[i + 1]]) <<" feet."<<endl;
		cout<<"Number of feet of cable required is "<< setprecision(2) << setiosflags(ios::fixed) << sum<<"."<<endl;
		}
	///////////////////////////////////
	#ifdef DEBUG
		system("pause");
	#endif // DEBUG
	return 0;
}