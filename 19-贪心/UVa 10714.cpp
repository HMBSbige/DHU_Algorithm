#include <iostream>
#include <algorithm>
using namespace std;
class blank{
public:
    size_t n;
    blank(size_t _n=1):n(_n){}
};
ostream& operator<<(ostream& os,blank&& a){
    for(size_t i=0;i<a.n;++i)
        os<<" ";
    return os;
}
int main()
{
    setlocale(LC_ALL,"");
    ios::sync_with_stdio(false);
    int T;
    int l,n,maxL,minL,m;
    while (cin>>T)
        while (T--) {
            cin>>l>>n;
            minL = maxL = 0;
            for (auto i = 0;i<n;++i) {
                cin>>m;
                maxL = max(maxL, max(m, l-m));
                minL = max(minL, min(m, l-m));
            }
            cout<<minL<<blank()<<maxL<<endl;
        }
    return 0;
}