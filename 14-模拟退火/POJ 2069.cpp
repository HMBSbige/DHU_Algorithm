#include <iostream> 
#include <iomanip>
#include <vector>
#include <cmath>
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
struct Point3D {
	double x, y, z;
	Point3D(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {}
};

Point3D operator - (const Point3D &a, const Point3D &b) {
	return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

double dist(const Point3D &a, const Point3D &b) {
	Point3D c = a - b;
	return sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
}
std::vector<Point3D> p;
size_t n;

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
	while (std::cin>>n && n) {
		std::vector<Point3D>(n).swap(p);
		for (i = 0; i < n; ++i) 
			std::cin >> p[i].x>>p[i].y>>p[i].z;
		Point3D s;
		double delta = 100, ans = 1e20;
		while (delta > 1e-6) {
			size_t d = 0;
			for (i = 1; i < n; ++i)
				if (dist(s, p[i]) > dist(s, p[d])) 
					d = i;
			double maxd = dist(s, p[d]);
			if (ans > maxd) 
				ans = maxd;
			s.x += (p[d].x - s.x) / maxd*delta;
			s.y += (p[d].y - s.y) / maxd*delta;
			s.z += (p[d].z - s.z) / maxd*delta;
			delta *= 0.98;
		}
		std::cout<< setiosflags(std::ios::fixed) << std::setprecision(5) << ans<< std::endl;
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