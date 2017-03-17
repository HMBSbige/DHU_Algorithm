/*
UVa 574 - Sum It Up
Coded by Guojin Zhu
Run time 0.008s
AC on October 30, 2012
*/
#include<iostream>
#include<vector>
using namespace std;
/////////////////////
class SumItUp{
private:
    int total;
    vector<int> integers;
    vector<int> sum;
    vector<vector<int> > allSums;
    void backtracking(int k, int s);
public:
    void initial(int t);
    void readNumbers(int n);
    void computing();
    void outResult();
};
void SumItUp::initial(int t){
    total = t;
    integers.clear();
    sum.clear();
    allSums.clear();
}
void SumItUp::readNumbers(int n){
    int x;
    while(n--){
        cin >> x;
        integers.push_back(x);
    }
}
void SumItUp::backtracking(int k, int s){
    if(s == 0){
        allSums.push_back(sum);
    }else if(s > 0){
        for(int i = k; i < integers.size(); i++){
            if((i == k)||(integers[i] != integers[i-1])){
                sum.push_back(integers[i]);
                backtracking(i+1, s-integers[i]);
                sum.pop_back();
            }
        }
    }
}
void SumItUp::computing(){
    backtracking(0, total);
}
void SumItUp::outResult(){
    cout << "Sums of " << total << ':' << endl;
    if(allSums.size() == 0){
        cout << "NONE" << endl;
    }else{
        for(int i = 0; i < allSums.size(); i++){
            for(int k = 0; k < allSums[i].size(); k++){
                if(k > 0){
                    cout << '+';
                }
                cout << allSums[i][k];
            }
            cout << endl;
        }
    }
}
/////////////////
int main(){
    SumItUp siu;
    int t, n;
    while((cin >> t >> n)&& n){
        siu.initial(t);
        siu.readNumbers(n);
        siu.computing();
        siu.outResult();
    }
    return 0;
}
/*
INPUT
4 6 4 3 2 2 1 1
4 7 4 4 3 2 2 1 1
5 3 2 1 1
400 12 50 50 50 50 50 50 25 25 25 25 25 25
0 0
---------------
OUTPUT
Sums of 4:
4
3+1
2+2
2+1+1
Sums of 4:
4
3+1
2+2
2+1+1
Sums of 5:
NONE
Sums of 400:
50+50+50+50+50+50+25+25+25+25
50+50+50+50+50+25+25+25+25+25+25
*/