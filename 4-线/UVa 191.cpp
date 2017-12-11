#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

int cmp(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x > 0)
        return 1;
    return -1;
}
class point
{
  public:
    double x, y;
    point(double, double);
    void input(std::istream &is);
    void input(double, double);
    point operator+(const point &b) const;
    point operator-(const point &b) const;
    bool operator==(const point &b) const;
    friend point operator*(const double &a, const point &b);
    friend point operator*(const point &a, const double &b);
    friend point operator/(const point &a, const double &b);
    double norm();                                       //向量的模
    friend double det(const point &a, const point &b);   //叉积
    friend double dot(const point &a, const point &b);   //点积
    friend double dist(const point &a, const point &b);  //两点间距离
    friend point rotate_point(const point &p, double A); // 向量op绕原点逆时针旋转A弧度
};
point::point(double a = 0.0, double b = 0.0) : x(a), y(b) {}
void point::input(std::istream &is)
{
    is >> x >> y;
}
void point::input(double a, double b)
{
    x = a;
    y = b;
}
point point::operator+(const point &b) const
{
    return point(this->x + b.x, this->y + b.y);
}
point point::operator-(const point &b) const
{
    return point(this->x - b.x, this->y - b.y);
}
bool point::operator==(const point &b) const
{
    return cmp(this->x - b.x) == 0 && cmp(this->y - b.y) == 0;
}
point operator*(const double &a, const point &b)
{
    return point(a * b.x, a * b.y);
}
point operator*(const point &a, const double &b)
{
    return point(b * a.x, b * a.y);
}
point operator/(const point &a, const double &b)
{
    return point(a.x / b, a.y / b);
}
double point::norm()
{
    return sqrt(x * x + y * y);
}
double det(const point &a, const point &b)
{
    return a.x * b.y - a.y * b.x;
}
double dot(const point &a, const point &b)
{
    return a.x * b.x + a.y * b.y;
}
double dist(const point &a, const point &b)
{
    return (a - b).norm();
}
point rotate_point(const point &p, double A)
{
    return point(p.x * cos(A) - p.y * sin(A), p.x * sin(A) + p.y * cos(A));
}
class line
{
  private:
  public:
    point a, b;
    line() {}
    line(point _a, point _b) : a(_a), b(_b) {}
};
double dis_point_segment(const point p, const point s, const point t) //返回点p到线段st的距离
{
    if (cmp(dot(p - s, t - s)) < 0)
        return (p - s).norm();
    if (cmp(dot(p - t, s - t) < 0))
        return (p - t).norm();
    return fabs(det(s - p, t - p) / dist(s, t));
}
point PointProjLine(const point p, const point s, const point t) //返回点p到线段st的垂足
{
    double r = dot(t - s, p - s) / dot(t - s, t - s);
    return s + r * (t - s);
}
bool PointOnSegment(point p, point s, point t) //点p是否在线段st上（包括端点）
{
    return cmp(det(p - s, t - s)) == 0 && cmp(dot(p - s, p - t)) <= 0;
}
bool isCoincident(line a, line b) //a,b是否重合
{
    double s1 = det(a.a - b.a, b.b - b.a);
    double s2 = det(a.b - b.a, b.b - b.a);
    if (cmp(s1 - s2) == 0 && cmp(s1) == 0)
        return true;
    return false;
}
bool isParallel(line a, line b) //a,b是否平行(不包括重合)
{
    //return !cmp(det(a.a-a.b,b.a-b.b));
    double s1 = det(a.a - b.a, b.b - b.a);
    double s2 = det(a.b - b.a, b.b - b.a);
    if (cmp(s1 - s2) == 0 && cmp(s1))
        return true;
    return false;
}
bool isIntersecting(line a, line b, point &res) //a,b是否相交,保存交点在res
{
    if (isParallel(a, b) || isCoincident(a, b))
        return false;
    double s1 = det(a.a - b.a, b.b - b.a);
    double s2 = det(a.b - b.a, b.b - b.a);
    res = (s1 * a.b - s2 * a.a) / (s1 - s2);
    return true;
}
//线段相交
bool cross(line a, line b)
{
    point res;
    return isIntersecting(a, b, res) && PointOnSegment(res, a.a, a.b) && PointOnSegment(res, b.a, b.b);
}
line move_d(line a, const double &len) //将直线a沿法向量方向平移len得到的直线
{
    point d = a.b - a.a;
    d = d / d.norm();
    d = rotate_point(d, pi / 2);
    return line(a.a + d * len, a.b + d * len);
}
class polygon
{
  public:
    size_t n;
    vector<point> a; //多边形的点，顺时针顺序
    polygon(size_t _n);
    double perimeter();     //返回多边形的周长
    double area();          //返回多边形的面积
    int isPointIn(point t); //判断点t是否在多边形的内部，0在多边形外，1在多边形内，2在多边形上
};
polygon::polygon(size_t _n) : n(_n)
{
    vector<point>(n).swap(a);
}
double polygon::perimeter()
{
    double sum = 0;
    for (size_t i = 0; i < n - 1; ++i)
        sum += (a[i + 1] - a[i]).norm();
    sum += (a[0] - a[n - 1]).norm();
    return sum;
}
double polygon::area()
{
    double sum = 0;
    for (size_t i = 0; i < n - 1; ++i)
        sum += det(a[i + 1], a[i]);
    sum += det(a[0], a[n - 1]);
    return sum / 2.0;
}
int polygon::isPointIn(point t)
{
    int num = 0, d1, d2, k;
    for (size_t i = 0; i < n - 1; ++i)
    {
        if (PointOnSegment(t, a[i], a[i + 1]))
            return 2;
        k = cmp(det(a[i + 1] - a[i], t - a[i]));
        d1 = cmp(a[i].y - t.y);
        d2 = cmp(a[i + 1].y - t.y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            ++num;
        if (k < 0 && d2 <= 0 && d1 > 0)
            --num;
    }
    if (PointOnSegment(t, a[n - 1], a[0]))
        return 2;
    k = cmp(det(a[0] - a[n - 1], t - a[n - 1]));
    d1 = cmp(a[n - 1].y - t.y);
    d2 = cmp(a[0].y - t.y);
    if (k > 0 && d1 <= 0 && d2 > 0)
        ++num;
    if (k < 0 && d2 <= 0 && d1 > 0)
        --num;
    return num != 0;
}
int main()
{
    ios::sync_with_stdio(false);
    int n;
    point a_line, b_line;
    point a_rectangle, b_rectangle;
    point d_rectangle, c_rectangle;
    point t1, t2;
    while (cin >> n)
        while (n--)
        {
            //input
            a_line.input(cin);
            b_line.input(cin);
            t1.input(cin);
            t2.input(cin);
            //left-top
            a_rectangle = point(min(t1.x, t2.x), max(t1.y, t2.y));
            //right-bottom
            c_rectangle = point(max(t1.x, t2.x), min(t1.y, t2.y));
            //right-top
            b_rectangle = point(c_rectangle.x, a_rectangle.y);
            //left-bottom
            d_rectangle = point(a_rectangle.x, c_rectangle.y);
            //
            line L(a_line, b_line);
            line l1(a_rectangle, d_rectangle); //left
            line l2(d_rectangle, c_rectangle); //botttom
            line l3(a_rectangle, b_rectangle); //top
            line l4(c_rectangle, b_rectangle); //right
            polygon rectangle(4);
            rectangle.a[0] = a_rectangle;
            rectangle.a[1] = b_rectangle;
            rectangle.a[2] = c_rectangle;
            rectangle.a[3] = d_rectangle;
            if (rectangle.isPointIn(a_line) != 0 || rectangle.isPointIn(b_line) != 0)
                cout << "T" << endl;
            else if (cross(L, l1) ||
                     cross(L, l2) ||
                     cross(L, l3) ||
                     cross(L, l4))
                cout << "T" << endl;
            else
                cout << "F" << endl;
        }
    return 0;
}