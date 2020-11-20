// 第四周程序填空题3
#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
    private:
        int m, n;
        int (*a)[5];
    public:
        Array2() { m = 1; n = 0;}
        Array2(int _m, int _n) : m(_m), n(_n) { a = new int[m][5]; }
        ~Array2() { delete[] a; }
        int * operator[](int i) { return a[i]; }
        int operator()(int i, int j) { return a[i][j]; }
        Array2& operator=(Array2& b){ // 这里不能用const，因为这样就不能调用重载的[]了
            m = b.m;
            n = b.n;
            this->a = new int[m][5];
            for (int i = 0; i < m;i++)
                for (int j = 0; j < n;j++)
                    a[i][j] = b[i][j];
            return *this;
        }

};

int main() {
    Array2 a(3,4);  // 二维数组初始化
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j; // 重载[]
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ","; // 重载()
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     
    b = a; // 重载 =
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}