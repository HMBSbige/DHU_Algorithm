/*
UVa 967 Circular
Coded by Guojin Zhu
Run Time 0.329s
AC on Nov. 30, 2015
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
/////////////////////
const int maxsize = 1000010;
/////////////////////
class Prime{
private:
    vector<int> composite;
public:
    bool yes(int m){return !composite[m];}
    void create(int n);
};
void Prime::create(int n){//sieve
    composite.clear();
    composite.resize(n+1);
    composite[0] = 1; // 0 is not a prime
    composite[1] = 1; // 1 is not a prime
    for(int i = 2; i <= sqrt(n); i++){
        if(!composite[i]){
            for(int j = i*i; j <= n; j += i){
                composite[j]++;
            }
        }
    }
}
/////////////////////////////
class CircularPrime{
private:
    vector<bool> cirPrime;
    string strNum;  // for circular shift 
    Prime p;
    void check();
    void produce(int k);
public:
    bool yes(int m){return cirPrime[m];}
    void create(int n);
};
void CircularPrime::create(int n){
    const int maxk = int(0.5 + log(double(maxsize))/log(double(10)));
   // cout << maxk << endl;
    p.create(n);
    cirPrime.clear();
    cirPrime.resize(n);
    for(int k = 3; k <= maxk; k++){
        strNum.resize(k);
        produce(k);
    }
}
void CircularPrime::produce(int k){
    static const string digit = "1379";
    if(k < 1){
        check();
    }else{
        for(int i = 0; i < 4; i++){
            strNum[k-1] = digit[i];
            produce(k-1);
        }
    }
}
void CircularPrime::check(){
    vector<int> v;
    const int w[6] = {1, 10, 100,1000,10000,100000};
    int x, ww;
    x = 0;
    for(int k = 0; k < strNum.size(); k++){
       x = 10*x + int(strNum[k] - '0');
    }
    if((!cirPrime[x])){// have not found
        v.clear();
        ww = w[strNum.size() - 1];
        for(int k = 0; k < strNum.size(); k++){
            if(p.yes(x)){
                v.push_back(x);
                x = 10*(x%ww) + x/ww;
            }else break;
        }
        if(v.size() == strNum.size()){
            for(int k = 0; k < v.size(); k++){
                x = v[k];
                cirPrime[x] = true;
            }
        }
    }
}
/////////////////////////////
class Circular{
private:
    int left;
    int right;
    int ans;
    vector<int> presum;
public:
    void preprocess(int n){
        CircularPrime cp;
        cp.create(n);
        presum.clear();
        int cnt;
        cnt = 0;
        for(int i = 0; i < n; i++){
            if(cp.yes(i)) cnt++;
            presum.push_back(cnt);
        }
    }
    void readCase(int first){
        left = first;
        cin >> right;
    }
    void computing(){ans = presum[right] - presum[left-1];}
    void outResult(){
        if(ans == 0){
            cout << "No Circular Primes." << endl;
        }else if (ans == 1){
            cout << "1 Circular Prime." << endl;
        }else{
            cout << ans << " Circular Primes." << endl;
        }
    }
};
//////////////////////
int main(){		// be int
	Circular c;
	int k;
	c.preprocess(maxsize);
	while((cin >> k) && (k != -1)){
	    c.readCase(k);
	    c.computing();
	    c.outResult();
	}
}
/*
INPUT
1000 1100
100 120
100 1000
-1
------------
OUTPUT
No Circular Primes.
1 Circular Prime.
12 Circular Primes.
*/
