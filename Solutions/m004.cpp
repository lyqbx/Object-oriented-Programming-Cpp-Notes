// 神秘的数组初始化
#include <iostream>
using namespace std;

int main()
{
	int * a[] = {
                0,0,new int,new int[6]
                // 这是指针数组，数组每个元素都是指针
// 在此处补充你的代码
};
	
	*a[2] = 123;
	a[3][5] = 456;
	if(! a[0] ) {
		cout << * a[2] << "," << a[3][5];
	}
	return 0;
}