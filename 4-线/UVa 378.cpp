#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps=1e-8;
const double pi=acos(-1.0);

int cmp(double x){
    if(fabs(x)<eps)
        return 0;
    if(x>0)
        return 1;
    return -1;
}
class point{
public:
    double x,y;
    point(double,double);
    void input(std::istream& is);
    void input(double,double);
    point operator +(const point &b) const;
    point operator -(const point &b) const;
    bool operator ==(const point &b) const;
    friend point operator *(const double &a,const point &b);
    friend point operator *(const point &a,const double &b);
    friend point operator /(const point &a,const double &b);
    double norm();//向量的模
    friend double det(const point &a,const point &b);//叉积
    friend double dot(const point &a,const point &b);//点积
    friend double dist(const point &a,const point &b);//两点间距离
    friend point rotate_point(const point &p,double A);// 向量op绕原点逆时针旋转A弧度
};
point::point(double a=0.0,double b=0.0):x(a),y(b){}
void point::input(std::istream& is){
    is>>x>>y;
}
void point::input(double a,double b){
    x=a;y=b;
}
point point::operator +(const point &b) const{
    return point(this->x+b.x,this->y+b.y);
}
point point::operator -(const point &b) const{
    return point(this->x-b.x,this->y-b.y);
}
bool point::operator ==(const point &b) const{
    return cmp(this->x-b.x)==0 && cmp(this->y-b.y)==0;
}
point operator *(const double &a,const point &b){
    return point(a*b.x,a*b.y);
}
point operator *(const point &a,const double &b){
    return point(b*a.x,b*a.y);
}
point operator /(const point &a,const double &b){
    return point(a.x/b,a.y/b);
}
double point::norm(){
    return sqrt(x*x+y*y);
}
double det(const point &a,const point &b)
{
    return a.x*b.y-a.y*b.x;
}
double dot(const point &a,const point &b)
{
    return a.x*b.x+a.y*b.y;
}
double dist(const point &a,const point &b)
{
    return (a-b).norm();
}
point rotate_point(const point &p,double A){
    return point(p.x*cos(A)-p.y*sin(A),p.x*sin(A)+p.y*cos(A));
}
class line{
private:
public:
    point a,b;
    line(){}
    line(point _a,point _b):a(_a),b(_b){}
};
double dis_point_segment(const point p,const point s,const point t)//返回点p到线段st的距离
{
    if(cmp(dot(p-s,t-s))<0)
        return (p-s).norm();
    if(cmp(dot(p-t,s-t)<0))
        return (p-t).norm();
    return fabs(det(s-p,t-p)/dist(s,t));
}
point PointProjLine(const point p,const point s,const point t)//返回点p到线段st的垂足
{
    double r=dot(t-s,p-s)/dot(t-s,t-s);
    return s+r*(t-s);
}
bool PointOnSegment(point p,point s,point t)//点p是否在线段st上（包括端点）
{
    return cmp(det(p-s,t-s))==0 && cmp(dot(p-s,p-t))<=0;
}
bool isCoincident(line a,line b)//a,b是否重合
{
    double s1=det(a.a-b.a,b.b-b.a);
    double s2=det(a.b-b.a,b.b-b.a);
    if(cmp(s1-s2)==0 && cmp(s1)==0)
        return true;
    return false;
}
bool isParallel(line a,line b)//a,b是否平行(不包括重合)
{
   //return !cmp(det(a.a-a.b,b.a-b.b));
    double s1=det(a.a-b.a,b.b-b.a);
    double s2=det(a.b-b.a,b.b-b.a);
    if(cmp(s1-s2)==0 && cmp(s1))
        return true;
    return false;
}
bool isIntersecting(line a,line b,point &res)//a,b是否相交,保存交点在res
{
    if(isParallel(a,b) || isCoincident(a,b))
        return false;
    double s1=det(a.a-b.a,b.b-b.a);
    double s2=det(a.b-b.a,b.b-b.a);
    res=(s1*a.b-s2*a.a)/(s1-s2);
    return true;
}
//线段相交
bool cross( line a, line b )
{
    point res;
    return isIntersecting(a,b,res) && PointOnSegment(res,a.a,a.b) && PointOnSegment(res,b.a,b.b);
}
line move_d(line a,const double &len)//将直线a沿法向量方向平移len得到的直线
{
    point d=a.b-a.a;
    d=d/d.norm();
    d=rotate_point(d,pi/2);
    return line(a.a+d*len,a.b+d*len);
}
int main()
{
    ios::sync_with_stdio(false);
    int N;
    point p[4];
    cin>>N;
    cout<<"INTERSECTING LINES OUTPUT"<<endl;
    while(N--){
        p[0].input(cin);
        p[1].input(cin);
        p[2].input(cin);
        p[3].input(cin);
        line a(p[0],p[1]);
        line b(p[2],p[3]);

        if(isCoincident(a,b))
            cout<<"LINE"<<endl;
        else if(isParallel(a,b))
            cout<<"NONE"<<endl;
        else{
            point res;
            isIntersecting(a,b,res);
            cout<<"POINT "<<setprecision(2)<<std::fixed<<res.x<<" "<<res.y<<endl;
        }
    }
    cout<<"END OF OUTPUT"<<endl;
    return 0;
}