#include <iostream> 
#include <iomanip>
#include <vector>
#include <algorithm>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
typedef uint64_t ull;
typedef int64_t ll;
#define PI acos(-1.0)
#define random(x) (rand()%x+1)
const int P = 20;
const int L = 25;
double X, Y;
size_t n;
double mindis[P];

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) :x(x), y(y) {}
	void input() {
		std::cin >> x >> y;
	}
};
std::vector<Point> p, tmp(P);
double dis(Point a, Point b)
{
	double x = a.x - b.x, y = a.y - b.y;
	return sqrt(x*x + y*y);
}

double cal(Point a)
{
	register size_t i;
	double maxn = 0;
	for (i = 0; i<n; i++) 
		maxn = std::max(maxn, dis(a, p[i]));
	return maxn;
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
	register size_t i;
	while (std::cin>>X>>Y>>n)
	{
		std::vector<Point>(n).swap(p);
		for (i = 0; i<n; ++i) 
			p[i].input();
		for (i = 0; i<P; ++i) {
			tmp[i].x = random(1000) / 1000.0*X;
			tmp[i].y = random(1000) / 1000.0*Y;
			mindis[i] = cal(tmp[i]);
		}
		double step = sqrt(X*X + Y*Y) / 2;
		while (step>1e-3) {
			for (i = 0; i<P; ++i) {
				for (int j = 0; j<L; ++j) {
					Point cur;
					double ang = random(1000) / 1000.0 * 2 * PI;
					cur.x = tmp[i].x + cos(ang)*step;
					cur.y = tmp[i].y + sin(ang)*step;
					if (cur.x<0 || cur.x>X || cur.y<0 || cur.y>Y) 
						continue;
					double val = cal(cur);
					if (val<mindis[i]) {
						mindis[i] = val;
						tmp[i] = cur;
					}
				}
			}
			step *= 0.85;
		}
		double ret = 1e20;
		Point u;
		for (i = 0; i<P; ++i) {
			if (mindis[i]<ret) {
				u = tmp[i];
				ret = mindis[i];
			}
		}
		std::cout << "(" << setiosflags(std::ios::fixed) << std::setprecision(1) << u.x << ","
			<< setiosflags(std::ios::fixed) << std::setprecision(1) << u.y << ")." << std::endl
			<< setiosflags(std::ios::fixed) << std::setprecision(1) << ret << std::endl;
	}
//////////////////////////////////////////////////////////////////////
#ifdef ofile
	outfile.close();
#endif
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}