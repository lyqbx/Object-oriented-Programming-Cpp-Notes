// 惊呆！Point竟然能这样输入输出
#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };
// 在此处补充你的代码
        friend ostream &operator<<(ostream &os, const Point & p);// 注意是友元，并且cout和cin的参数不同，cin需要修改对象的值
        friend istream &operator>>(istream &is, Point & p);
};

ostream &operator<<(ostream &os, const Point & p){
    os << p.x << "," << p.y;
    return os;
}
istream &operator>>(istream &is,  Point & p){
    is >> p.x >> p.y;
    return is;
};

int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}