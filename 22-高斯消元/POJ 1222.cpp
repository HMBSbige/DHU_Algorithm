#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


//取字符c的第i个bit.
int Getbit(char c, int i)
{
	return (c >> i) & 1;
}

//把c的第i位设置成v
void setbit(char &c, int i, int v)
{
	if (v)
		c |= (1 << i);
	else
		c &= ~(1 << i);
}

//把c的第i位翻转.(1 翻为0 , 0 翻为 1).
void flipbit(char & c, int i)
{
	c ^= (1 << i);
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	//初始灯的状态.
	string orilight;
	orilight.resize(10);
	//结果的操作数.
	string result;
	result.resize(10);
	//中间操作时灯的状态.
	string light;
	light.resize(10);

	cin >> T;
	for (int t = 1; t <= T; ++t) 
	{
		for (int i = 0; i<5; ++i)
			for (int j = 0; j<6; ++j) {
				int k;
				cin >> k;
				setbit(orilight[i], j, k);
			}
		for (int n = 0; n<64; ++n) 
		{
			light = orilight;
			int switchs = n;//开关的状态存在switchs中,
			for (int i = 0; i<5; ++i) 
			{
				result[i] = switchs;
				for (int j = 0; j<6; ++j) {// 对同一行(即第i行)的灯进行处理.
					if (Getbit(switchs, j)) {
						if (j>0)
							flipbit(light[i], j - 1);
						flipbit(light[i], j);
						if (j < 5)
							flipbit(light[i], j + 1);
					}
				}
				if (i < 4)//因为下一行的操作是根据上一行的状态进行的操作,所以不用再去管上一行.
					light[i + 1] ^= switchs;//影响第i+1行的灯的状态.
				switchs = light[i];//因为下一行的操作是要根据上一行来进行的,所以需要在把switch再来赋值一波.
				//因为上一行灯的状态就是下一行的操作状态.
			}
			if (light[4] == 0) {
				cout << "PULLZE #" << t << endl;
				for (int i = 0; i<5; ++i) {
					for (int j = 0; j<6; ++j) {
						cout << Getbit(result[i], j);
						if (j<5)
							cout << " ";
						else
							cout << endl;
					}
				}
				break;
			}
		}
	}
}