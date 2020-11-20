// 奇怪的类复制，使输出为9,22,5
#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    Sample() : v(0) { cout << "默认" << endl; } //1
    Sample(int n) { v = n;
        cout << "类型转换" << endl;
    }                                           //2
    Sample(const Sample &s) { v = s.v + 2;
        cout << "复制" << endl;
    } //3
    // 在此处补充你的代码
};
void PrintAndDouble(Sample o)
{
    cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);    //2
	Sample b = a;   //3
	PrintAndDouble(b);  //3
	Sample c = 20;  //2
	PrintAndDouble(c);  //3
	Sample d;   //1
	d = a;  //不调用
	cout << d.v << endl;
	Sample *p=new Sample[10];
	cout << p->v << (p+1)->v;
	;
	return 0;
}