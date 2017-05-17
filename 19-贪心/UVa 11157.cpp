#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int t,T=0,n, d;
    cin >> t;
    while(t--)
        while(cin >> n >> d) {
            char a;
            int b;
            vector<int> V;
            V.push_back(0);
            V.push_back(d);
            for(auto i=0;i<n;++i) {
                cin >> a;cin.ignore();cin >> b;
                V.push_back(b);
                if (a=='B')
                    V.push_back(b);
            }
            sort(V.begin(), V.end());
            int ans = 0;
            for(size_t i=3;i<V.size(); i+=2)
                ans = max(ans, V[i]-V[i-2]);
            for(size_t i=2;i<V.size(); i+=2)
                ans = max(ans, V[i]-V[i-2]);
            cout << "Case " << ++T << ": " << ans << endl;
        }
    return 0;
}