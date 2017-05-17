#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct qujian
{
    int start;
    int end;
    void operator ()(const int& a,const int& b){
        start=a;
        end=b;
    }
};
int cmp (const qujian& a,const qujian& b)
{
    return a.end > b.end;
}
int main()
{
    //setlocale(LC_ALL,"");
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while (T--)
    {
        auto start = 0,end = 0;
        auto _start=0,_end=0;
        vector<qujian> q;
        cin>>end;//M
        qujian temp_qj;
        while (cin>>_start>>_end && (_start||_end)){
            temp_qj(_start,_end);
            q.push_back(temp_qj);
        }
        sort(q.begin(),q.end(),cmp);
        vector<qujian> ans;
        while(start<end)
        {
            int i;
            for (i=0;i<q.size();++i)
            {
                //找到最大能覆盖剩余区间的区间
                if (q[i].start <= start && q[i].end > start)
                {
                    start = q[i].end;
                    ans.push_back(q[i]);
                    break;
                }
            }
            //如果没有一个满足条件的区间，直接结束
            if (i==q.size())
                break;
        }
        if(start<end)
            cout<<0<<endl;
        else
        {
            cout<<ans.size()<<endl;
            for (auto&x:ans)
                cout<<x.start<<" "<<x.end<<endl;
        }
        //Print a blank line between the outputs for two consecutive test cases.
        if (T)
            cout<<endl;
    }
    return 0;
}