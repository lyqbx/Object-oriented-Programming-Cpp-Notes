// 看上去像多态
#include <iostream>
using namespace std;
class B { 
	private: 
		int nBVal; 
	public: 
		void Print() 
		{ cout << "nBVal="<< nBVal << endl; } 
		void Fun() 
		{cout << "B::Fun" << endl; } 
		B ( int n ) { nBVal = n;} 
};
class D:public B{
    private:
        int nDval;
    public:
        void Print()
        {
            cout << "nBVal=" << 3 * nDval << endl;
            cout << "nDVal=" <<  nDval << endl;
        }
        void Fun()
        {
            cout << "D::Fun" << endl;
        }
        D(int n):B(3*n) { nDval = n; }
};
// 在此处补充你的代码
int main() { 
	B * pb; D * pd; 
	D d(4); 
    d.Fun(); //1
	pb = new B(2); pd = new D(8); 
	pb -> Fun();//2
    pd->Fun(); //3 
	pb->Print ();//4
    pd->Print ();//5 这里是派生类的指针，不是多态！只有通过基类指针调用同名虚函数才是多态
	pb = & d; 
    pb->Fun();//7 这里输出的b，所以不是多态
	pb->Print(); //8 4*3 
	return 0;
}