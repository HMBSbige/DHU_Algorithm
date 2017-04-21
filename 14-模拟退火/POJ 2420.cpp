#include <iostream> 
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
const int num = 100;
const int cnt = 20;
const double PI = acos(-1.0);
struct point
{
	double px, py, dis;
};
point ans[100];
double x[105], y[105];
double get_dis(double a, double b, double c, double d)
{
	return sqrt((c - a)*(c - a) + (d - b)*(d - b));
}
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef ofile	
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", std::ios::trunc);
	std::cout.rdbuf(outfile.rdbuf());
#endif
//////////////////////////////////////////////////////////////////////
	//srand((unsigned)time(NULL));
	register size_t i,j,k,n;
	std::cin >> n;
	for (i = 0; i<n; ++i)
		std::cin >> x[i]>>y[i];
	for (i = 0; i<num; ++i)
	{
		ans[i].px = 1.0*(rand() % 32767) / 32767 * 10000;
		ans[i].py = 1.0*(rand() % 32767) / 32767 * 10000;
		ans[i].dis = 0;
		for (j = 0; j<n; ++j)
		{
			ans[i].dis += get_dis(ans[i].px, ans[i].py, x[j], y[j]);
		}
	}
	double temp = get_dis(0, 0, 10000, 10000);
	while (temp>0.2)
	{
		for (i = 0; i<num; ++i)
		{
			double fx, fy;
			for (j = 0; j<cnt; ++j)
			{
				double cur = 2.0*PI*(rand() % 32767) / 32767;
				fx = ans[i].px + cos(cur)*temp;
				fy = ans[i].py + sin(cur)*temp;
				if (fx<0 || fx>10000 || fy<0 || fy>10000)
					continue;
				double dist = 0;
				for (k = 0; k<n; ++k)
				{
					dist += get_dis(fx, fy, x[k], y[k]);
				}
				if (dist<ans[i].dis)
				{
					ans[i].px = fx;
					ans[i].py = fy;
					ans[i].dis = dist;
				}
			}
		}
		temp *= 0.8;
	}
	double ans_dis = 1e12;
	for (i = 0; i < num; ++i)
		ans_dis = std::min(ans_dis, ans[i].dis);
	if (ans_dis >= 0)
		ans_dis += 0.5;
	else
		ans_dis -= 0.5;
	std::cout << (long long)ans_dis << std::endl;
//////////////////////////////////////////////////////////////////////
#ifdef ofile
	outfile.close();
#endif
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}