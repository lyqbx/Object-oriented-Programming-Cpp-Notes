// 很难蒙混过关的CArray3D三维数组模板类
// 要创造内存连续的二维数组，那么只需要平铺，然后重载一次[]，让s[]返回指向当前行的指针
// 但是如果是三维数组，那么s[]指向一个拥有指针的对象，然后s[][]返回一个指针
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
public:
    T *p3 ;
    int a1, a2, a3;

    class CArray2D
    {
    private:
        T *p2;
        int a1, a2,a3;

    public:
        void set(int i,T* p3,int _a1,int _a2,int _a3)
        {
            a1 = _a1;
            a2 = _a2;
            a3 = _a3;
            p2 = p3 + i * a2 * a3;
        }
        T *operator[](int i)
        {
            return p2 + i * a3 ;
        }
        operator void *()
        {
            return p2;
        }
    };
    CArray2D *arr2;

    CArray3D(int _a1, int _a2, int _a3) : a1(_a1), a2(_a2), a3(_a3)
    {
        p3 = new T[a1 * a2 * a3];
        arr2 = new CArray2D[a1];
        int j = 0;
        for (CArray2D *i = arr2; j < a1; j++)
        {
            i->set(j,p3,a1,a2,a3);
            i++;
        }
    }
    CArray2D operator[](int i)
    {
        return arr2[i];
    }
    ~CArray3D()
    {
        delete[] arr2;
        delete[] p3;
    }
};
// ~CArray3D()
// {
//     cout << "3d des" << endl;
//     delete[] arr3;
// }

// 不能像注释这么写，因为这题要求行与行之间的空间是连续的
/*
    CArray3D(int a1, int a2, int a3):a(a1),b(a2),c(a3)
    {
        arr = new T **[a1];
        for (int i = 0; i < a1; i++)
        {
            arr[i] = new T *[a2];
            for (int j = 0; j < a2; j++)
            {
                arr[i][j] = new T[a3];
            }
        }
    }
    T **operator[](int i) { return arr[i]; }
    ~CArray3D(){
        for (int i = 0; i < a;i++)
        {
            for (int j = 0; j < b;j++)
                delete[] arr[i][j];
            delete[] arr[i];
        }
        delete[] arr;
    }
    */

CArray3D<int> a(3, 4, 5);
CArray3D<double> b(3, 2, 2);
void PrintA()
{
    for (int i = 0; i < 3; ++i)
    {
        cout << "layer " << i << ":" << endl;
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 5; ++k)
                cout << a[i][j][k] << ",";
            cout << endl;
        }
    }
}
void PrintB()
{
    for (int i = 0; i < 3; ++i)
    {
        cout << "layer " << i << ":" << endl;
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
                cout << b[i][j][k] << ",";
            cout << endl;
        }
    }
}

int main()
{

    int No = 0;
    for (int i = 0; i < 3; ++i)
    {
        a[i];
        for (int j = 0; j < 4; ++j)
        {
            a[j][i];
            for (int k = 0; k < 5; ++k)
            {

                a[i][j][k] = No++;
            }
            a[j][i][i];
        }
    }
    PrintA();

    memset(a[1], -1, 20 * sizeof(int)); // 这里相当于把一个二维数组用内存修改值了，但是动态二维数组的每一行之间内存并不连续！
    memset(a[1], -1, 20 * sizeof(int)); // 所以这里就要保证a[1],a[2]是连续的，new就不行了

    PrintA();
    memset(a[1][1], 0, 5 * sizeof(int));
    PrintA();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                b[i][j][k] = 10.0 / (i + j + k + 1);
    PrintB();
    int n = a[0][1][2];
    double f = b[0][1][1];
    cout << "****" << endl;
    cout << n << "," << f << endl;

    system("pause");
    return 0;
}