// 返回什么好呢
#include <iostream>
using namespace std;
class A {
public:
	int val;
    A() : val(123){}
    A &GetObj() { return *this; }   //引用能作为等号的左值
    A(int n) { val = n;}
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m; // 类型转换函数
		cout << a.val << endl;
		a.GetObj() = A(n);  // 也是类型转换函数
		cout << a.val<< endl;
	}
	return 0;
}