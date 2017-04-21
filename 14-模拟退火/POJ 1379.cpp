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
const double PI = acos(-1.0);
using namespace std;
struct point {
	double x, y;
};
std::vector<point> po;
point ans_po[100];
size_t X, Y, n;
double ans[100];
double dis(point &a, point &b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
double find_max(point &a) {
	double ans = 1e12, t;
	for (int i = 0; i<n; i++) {
		t = dis(a, po[i]);
		ans = std::min(t, ans);
	}
	return ans;
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
	register size_t i, j, t;
	std::cin >> t;
	double step, theta, now;
	point temp;
	//srand(unsigned(time(NULL)));
	while (t--) {
		std::cin >> X>>Y>>n;
		std::vector<point>(n).swap(po);
		for (i = 0; i<n; ++i)
			std::cin >> po[i].x>>po[i].y;
		for (i = 0; i<30; ++i) {
			ans_po[i].x = (rand() % 1001) / 1000.0*X;
			ans_po[i].y = (rand() % 1001) / 1000.0*Y;
			ans[i] = find_max(ans_po[i]);
		}
		step = (double)std::max(X, Y);
		while (step>1e-8) {
			for (i = 0; i<30; ++i) {
				theta = (rand() % 1001) / 500.00*PI;
				for (j = 0; j<30; ++j) {
					temp.x = ans_po[j].x + cos(theta)*step;
					temp.y = ans_po[j].y + sin(theta)*step;
					if (temp.x>X || temp.x<0 || temp.y>Y || temp.y<0)
						continue;
					now = find_max(temp);
					if (now > ans[j]) {
						ans[j] = now;
						ans_po[j] = temp;
					}
						
				}
			}
			step *= 0.8;
		}
		j = 0;
		now = ans[0];
		for (i = 1; i<30; ++i)
			if (ans[i] > now) {
				now = ans[i];
				j = i;
			}
		std::cout << "The safest point is (" << std::fixed << std::setprecision(1) << ans_po[j].x << ", "
			<< std::fixed << std::setprecision(1) << ans_po[j].y << ")." << std::endl;
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