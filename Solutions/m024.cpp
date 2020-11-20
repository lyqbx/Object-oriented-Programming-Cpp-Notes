// Fun 和 Do
#include <iostream> 
using namespace std;
class A { 
	private: 
	int nVal; 
	public: 
	void Fun() 
	{ cout << "A::Fun" << endl; }; 
	void Do() 
	{ cout << "A::Do" << endl; } 
}; 
class B:public A { 
	public: 
	virtual void Do()   // 这里是多态
	{ cout << "B::Do" << endl;} 
}; 
class C:public B { 
	public: 
	void Do( )  // 这里是多态 和上面是一对儿
	{ cout <<"C::Do"<<endl; } 
	void Fun() 
	{ cout << "C::Fun" << endl; } 
}; 
void Call(
    B &p
// 在此处补充你的代码
) { 
	p.Fun(); p.Do(); 
} 
int main() { 
	C c; 
	Call( c); 
	return 0;
}