/*
UVa112 - Tree Summing
Coded by Guojin Zhu
Run Time 0.115s
AC on March 24, 2015
*/
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
//////////////////////
class TreeSumming{
private:
    int intNum;
    vector<int> path;
    bool found;
    void verify();
public:
    void initial(int);
    char readBracket();
    bool readTree();
    void outResult();
};
void TreeSumming::initial(int n){
    intNum = n;
    path.clear();
    found = false;
}
void TreeSumming::verify(){
    int sum;
    sum = 0;
    for(int i = 0; i < path.size(); i++){
        sum += path[i];
    }
    if(sum == intNum){
        found = true;
    }
}
void TreeSumming::outResult(){
    if(found){
        cout << "yes" << endl;
    }else{
        cout << "no" << endl;
    }
}
char TreeSumming::readBracket(){
    char c;
    scanf("%c", &c);
    while((c == ' ') || (c =='\n')){
        scanf("%c", &c);
    }
    return c;
}
bool TreeSumming::readTree(){
    int n;
    char b;
    bool nonempty;
    scanf("%d", &n);
    b = readBracket(); 
    if(b == '('){
        path.push_back(n); //tracking
        nonempty = readTree();// left child
        b = readBracket(); 
        nonempty |= readTree(); //right child
        b = readBracket(); //skip right bracket
        if (!nonempty){
             //cout << "leaf" << endl;
             verify();
        }
        path.pop_back(); //backtracking
        return true;
    }else{
        return false; //empty tree
    }
}
///////////////////////////////
int main(){
    TreeSumming ts;
    int n;
    while(cin >> n){
        ts.initial(n);
        ts.readBracket();//skip left bracket
        ts.readTree();
        ts.outResult();
    }
	return 0;	// must return 0;
}
/*
INPUT
22 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
20 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
10 (3 
     (2 (4 () () )
        (8 () () ) )
     (1 (6 () () )
        (4 () () ) ) )
5 ()
----------------
OUTPUT
yes
no
yes
no
*/