/*
UVa497 - Strategic Defense Initiative
Run Time 0.012s
Solved by Guojin Zhu
AC on April 5, 2013
*/
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<climits>
using namespace std;
//////////////////////////
struct node{
    int value;
    int pred;
    node(int a = 0, int b = 0){value = a; pred = b;}
};
class StrategicDefenseInitiative{
private:
    vector<int> sequence; //altitudes
    int maxLength;
    vector<node> chain;
    int maxInex;
public:
    void initial();
    void readCase();
    void computing();
    void outResult();
};
void StrategicDefenseInitiative::initial(){
    sequence.clear();
    maxLength = 0;
    chain.clear();
}
void StrategicDefenseInitiative::readCase(){
    int x;
    string line;
    while(getline(cin, line) && (line.size() > 0)){
        stringstream(line) >> x;
        sequence.push_back(x);
    }
}
void StrategicDefenseInitiative::computing(){
    vector<int> minVisited;
    vector<int> numVisited;
    int t;
    numVisited.push_back(-1); //for the sentinel
    minVisited.push_back(INT_MIN);
    for(int i = 0; i < sequence.size(); i++){//nlog(n)
        //cout << sequence[i] << endl;
        t = lower_bound(minVisited.begin(), minVisited.end(), sequence[i]) - minVisited.begin();
        if(t >= minVisited.size()){ // t indicates the new length
            minVisited.push_back(sequence[i]);
            numVisited.push_back(chain.size());
            chain.push_back(node(sequence[i], numVisited[t-1]));
        }else if(sequence[i] < minVisited[t]){//sequence[i] is the smallest
            minVisited[t] = sequence[i];
            numVisited[t] = chain.size();
            chain.push_back(node(sequence[i], numVisited[t-1]));
        }
    }
    maxLength = numVisited.size() - 1;
    maxInex = numVisited[maxLength];
}
void StrategicDefenseInitiative::outResult(){
    cout << "Max hits: " << maxLength << endl;
    stack<int> s;
    int p = maxInex;
    while(p > -1){
        s.push(chain[p].value);
        p = chain[p].pred;
    }
    while(!s.empty()){
        cout << s.top() << endl;
        s.pop();
    }
}
//////////////////////////////
int main(){
    StrategicDefenseInitiative sdi;
    int n;
    string str;
    getline(cin, str);
    stringstream(str) >> n;
    getline(cin, str); // skip the blank line
    for(int i = 0; i < n; i++){
        sdi.initial();
        sdi.readCase();
        sdi.computing();
        if (i > 0){
            cout << endl;
        }
        sdi.outResult();
    }
    return 0;
}
/*
INPUT
2

1
6
2
3
5

1
6
2
3
5
----------------
OUTPUT
Max hits: 4
1
2
3
5

Max hits: 4
1
2
3
5
*/