#include <iostream>
//#define DEBUG
using namespace std;
typedef int ull;
//22 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
char input()
{
	char c;
	cin >> c;
	while (c == ' ' || c == '\n')
		cin >> c;
	return c;
}
bool solve(ull n, bool *isleaf) {
	char temp;
	bool b=false,l = false, r = false;
	ull  value;
	cin>>value;
	cin.clear();
	temp = input();
	
	if (temp == '(') {
		if (solve(n - value, &l))
			b = true;
		input();
		if (solve(n - value, &r))
			b = true;
		input();
		if (l && r) 
			b= (n == value);
	}
	else 
		*isleaf =true;
	return b;
}
int main()
{
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
	///////////////////////////////////
	ull n;
	bool _;
	while (cin >> n) {
		input();
		if (solve(n, &_))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	///////////////////////////////////
	#ifdef DEBUG
		system("pause");
	#endif // DEBUG
	return 0;
}
/*
22 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
20 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
10 (3
(2 (4 () () )
(8 () () ) )
(1 (6 () () )
(4 () () ) ) )
5 ()

*/