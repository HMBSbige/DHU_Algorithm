#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;
//#define DEBUG
#ifdef DEBUG
#include <fstream>
ofstream outfile;
#endif // DEBUG
/////////////////////////////////////////////////
int t, n;
int ar[20];
map<vector<int>, bool > solutions;
vector<int> v;
void search(int k, int m, int sum, vector<int> v) {
	if (sum == t) {
		if (solutions[v] == true) return;
		solutions[v] = true;
		for (int i = 0; i < k; i++) {
			cout << v[i];
			if (i != k - 1)
				cout << "+";
		}
		cout << endl;
		return;
	}
	if (sum > t || m == n) return;
	for (int i = m; i < n; i++) {
		v.push_back(ar[i]);
		search(k + 1, i + 1, sum + ar[i], v);
		v.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef DEBUG
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", ios::trunc);
#endif // DEBUG
	///////////////////////////////////
	while(cin>>t>>n && t && n) {
		for (int i = 0; i < n; i++)
			cin>>ar[i];
		solutions.clear();
		cout << "Sums of " << t << ":" << endl;;
		search(0, 0, 0, v);
		if (solutions.size() == 0)
			cout << "NONE" << endl;;
	}
	///////////////////////////////////
#ifdef DEBUG
	outfile.close();
	system("pause");
#endif // DEBUG
	return 0;
}