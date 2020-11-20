// 看上去好坑的运算符重载
#include <iostream> 
using namespace std;
class MyInt 
{ 
	int nVal; 
	public: 
	MyInt( int n) { nVal = n ;}
    MyInt & operator-(int n){
        nVal -= n;
        return *this;
    }
    operator int(){
        return nVal;
    }
// 在此处补充你的代码
}; 
int Inc(int n) {
	return n + 1;
}
int main () { 
    // 对每组数据，输出一行，包括两个整数，n-5和n-8
	int n;
	while(cin >>n) {
		MyInt objInt(n); 
		objInt-2-1-3; 
		cout << Inc(objInt);
		cout <<","; 
		objInt-2-1; 
		cout << Inc(objInt) << endl;
	}
	return 0;
}