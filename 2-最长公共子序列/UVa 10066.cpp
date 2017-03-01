#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#define max(a,b) (a>b)? a:b
using namespace std;

vector<vector<int> > table;
set<vector<int> > setOfLCS;

template <class T> T Reverse(T str)
{
	reverse(str.begin(), str.end());
	return str;
}
template <class T> int lcs(T X,T Y)
{
    int m=X.size();
    int n=Y.size();
	table = vector<vector<int> >(m+1,vector<int>(n+1));
	for(int i=0; i<m+1; ++i)
	{
		for(int j=0; j<n+1; ++j)
		{
			if (i == 0 || j == 0)
				table[i][j] = 0;

			else if(X[i-1] == Y[j-1])
				table[i][j] = table[i-1][j-1] + 1;

			else
				table[i][j] = max(table[i-1][j], table[i][j-1]);
		}
	}
	return table[m][n];
}
template <class T> void traceBack(int i,int j,T X,T Y,T lcs_str)
{
	while (i>0 && j>0)
	{
		if (X[i-1] == Y[j-1])
		{
			lcs_str.push_back(X[i-1]);
			--i;
			--j;
		}
		else
		{
			if (table[i-1][j] > table[i][j-1])
				--i;
			else if (table[i-1][j] < table[i][j-1])
				--j;
			else
			{
				traceBack<T>(i-1, j,X,Y,lcs_str);
				traceBack<T>(i, j-1,X,Y,lcs_str);
				return;
			}
		}
	}
	setOfLCS.insert(Reverse<T>(lcs_str));
}
int main()
{
	int m,n,N=0;
	vector<int> _,__;
	while(cin>>m>>n && (m!=0 || n!=0)){
        ++N;
        vector<int>().swap(_);
        vector<int>().swap(__);
        _.resize(m);
        __.resize(n);
        for(int i=0;i<m;++i)
            cin>>_[i];
        for(int i=0;i<n;++i)
            cin>>__[i];
        int length = lcs<vector<int> >(_, __);
        cout<<"Twin Towers #"<<N<<endl;
        cout<<"Number of Tiles : "<<length<<endl<<endl;
	}
	return 0;
}