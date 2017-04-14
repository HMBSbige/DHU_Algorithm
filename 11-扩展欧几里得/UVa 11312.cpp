#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef int64_t ll;
ll exgcd(ll m,ll n,ll &x,ll &y)
{
    ll x1,y1,x0,y0;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    ll r=m%n;
    ll q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}
bool isOverBorder(ll x,ll y,ll t,ll l,ll r,ll n){
    ll now=1;
    while(1){
        if(now==t){
            if(x==0 && y==0)
                return true;
            return false;
        }
        if(now+r>n || y==0){
            if(now-l<1)
                return false;
            else{
                if(x<0)
                    return false;
                now-=l;
                --x;
            }
        }
        else if(now+r<=n)
        {
            ll step=floor((t-now)/r);
            if(step<=0){
                if(y>0){
                   now+=r;
                    --y;
                }else
                    return false;
            }
            else{
                if(y-step>0){
                   now+=step*r;
                    y-=step;
                }else if(y-step==0)
                {
                    now+=step*r;
                    y-=step;
                }else
                    return false;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    size_t c;
    cin>>c;
    ll n,l,r,t,d,x,y,X,Y,INT,xrange,yrange;
    while(c--){
        cin>>n>>l>>r>>t;//lx+ry=t-1;
        d=exgcd(l,r,x,y);
        if((t-1)%d){
            cout<<"uh-oh!"<<endl;
            continue;
        }
        x*=(t-1)/d;
        y*=(t-1)/d;
        xrange=floor((double)(-x)/(r/d));//X=x+r/d*INT<0
        yrange=floor((double)y/(l/d));//Y=y-l/d*INT>0
        INT=min(xrange,yrange);
        X=x+r/d*INT;
        Y=y-(l/d)*INT;
        if(!isOverBorder(-X,Y,t,l,r,n)){
            cout<<"uh-oh!"<<endl;
            continue;
        }
        cout<<Y-X<<endl;
    }
    return 0;
}
/*
4
2563453 33 98 1694866
8042308 89 41 2450297
8999689 59 41 5196011
887826 40 14 211256

17344
59776
126810
uh-oh!
*/
