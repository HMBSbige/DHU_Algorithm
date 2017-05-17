#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    while (cin>>n && n)
    {
        vector<int> a(n);
        map<int,int> num;
        auto k = 0;
        for (auto&x:a)
        {
            cin>>x;
            ++num[x];
            k = max(k, num[x]);
        }
        sort(a.begin(), a.end());
        cout<<k<<endl;
        for (auto i = 0; i < k; ++i)
        {
            cout<<a[i];
            for (auto j = i + k; j < n; j += k)
                cout<<" "<<a[j];
            cout<<endl;
        }
    }
    return 0;
}