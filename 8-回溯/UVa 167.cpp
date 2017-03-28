#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
//#define DEBUG
using namespace std;

/////////////////////////////////////////////////
class EightQueen {
public:
	vector<vector<int> >pos;
	EightQueen(): pos(92), gEightQueen(8, 0)
	{
		eight_queen(0);
	}
private:
	vector<int> gEightQueen;
	int gCount = 0;
	bool check_pos_valid(int loop, int value)//检查是否存在有多个皇后在同一行/列/对角线的情况
	{
		int index;
		int data;
		for (index = 0; index < loop; ++index)
		{
			data = gEightQueen[index];
			if (value == data)
				return false;
			if ((index + data) == (loop + value))
				return false;
			if ((index - data) == (loop - value))
				return false;
		}
		return true;
	}
	void eight_queen(int index)
	{
		int loop;
		for (loop = 0; loop < 8; loop++)
		{
			if (check_pos_valid(index, loop))
			{
				gEightQueen[index] = loop;
				if (7 == index)
				{
					pos[gCount++] = gEightQueen;
					gEightQueen[index] = 0;
					return;
				}
				eight_queen(index + 1);
				gEightQueen[index] = 0;
			}
		}
	}
};

int main()
{
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
	///////////////////////////////////
	EightQueen eq;
	register int i,j,T;
	int ans,temp;
	int CheckerBoard[64];
	cin >> T;
	while (T--) {
		ans = 0;
		for (i = 0; i < 64; ++i)
			cin >> CheckerBoard[i];
		for (i = 0; i < 92; ++i) {
			temp = 0;
			for (j = 0; j < 8; ++j)
				temp += CheckerBoard[8*j+eq.pos[i][j]];
			ans = max(ans, temp);
		}
		cout << setiosflags(ios::right) << setw(5) << ans << endl;
	}
	
	///////////////////////////////////
	#ifdef DEBUG
		system("pause");
	#endif // DEBUG
	return 0;
}