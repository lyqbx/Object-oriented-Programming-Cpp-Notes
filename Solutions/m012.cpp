// 这个指针哪来的
#include <iostream>
using namespace std;

struct A
{
	int v;
	A(int vv):v(vv) { }
// 在此处补充你的代码
    const A * getPointer() const { 
        A a(5);
        a.v++;
        cout << a.v;
        return this;
    } // a是常量对象，调用的函数getPointer就得是常量函数
    // 常量函数不改变其作用对象的值，因为this就是const类型的
};

int main()
{
	const A a(10);
	const A * p = a.getPointer();
	cout << p->v << endl;
	return 0;
}