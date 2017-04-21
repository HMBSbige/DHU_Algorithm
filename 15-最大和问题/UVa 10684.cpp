#include <iostream> 
//#define DEBUG
//#define ofile
#ifdef ofile
#include <fstream>	
std::ofstream outfile;
#endif // ofile
//////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "");
#ifdef ofile	
	outfile.open("C:\\Users\\Bruce Wayne\\Desktop\\out.txt", std::ios::trunc);
	std::cout.rdbuf(outfile.rdbuf());
#endif
//////////////////////////////////////////////////////////////////////
	int N, num;
	while (std::cin>>N && N) {
		int Max = 0;
		int MSS = -1;
		while (N--) {
			std::cin >> num;
			if (MSS < 0)
				MSS = num;
			else 
				MSS += num;
			if (MSS > Max) 
				Max = MSS;
		}
		if (Max > 0)
			std::cout << "The maximum winning streak is " << Max << "." << std::endl;
		else
			std::cout << "Losing streak." <<std::endl;
	}
//////////////////////////////////////////////////////////////////////
#ifdef ofile
	outfile.close();
#endif
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}