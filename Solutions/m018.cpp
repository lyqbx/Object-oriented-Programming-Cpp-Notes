// 别叫，这个大整数已经很简化了！
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt
{
    char hugeint[210];
    int length;
    // 在此处补充你的代码
public:

    CHugeInt(char *s)
    {
        strcpy(hugeint, s);
        length = strlen(hugeint);
    }
    CHugeInt(int n) // 类型转换构造函数
    {
        sprintf(hugeint, "%d", n);
        length = strlen(hugeint);
    }
    CHugeInt(const CHugeInt &a) // 复制构造函数
    {
        strcpy(hugeint, a.hugeint);
        length = a.length;
    }
    CHugeInt &operator=(const CHugeInt &a)
    {
        strcpy(hugeint, a.hugeint);
        length = a.length;
        return *this;
    }
    friend CHugeInt operator+(const CHugeInt &a, const CHugeInt &b);
    friend void operator+=(CHugeInt &a, const CHugeInt &b);
    CHugeInt &operator++();
    CHugeInt operator++(int);
    friend ostream &operator<<(ostream &os, const CHugeInt &a);
};
CHugeInt operator+(const CHugeInt &a, const CHugeInt &b)
{
    int i, j;
    int carry = 0;
    char hugeint[210];
    const CHugeInt *max, *min;
    if(a.length > b.length)
    {
        max = &a;
        min = &b;
    }
    else
    {
        max = &b;
        min = &a;
    }
    hugeint[max->length] = '\0';
    for (i = max->length - 1, j = min->length - 1; j >= 0; i--,j--)
    {
        char tmp = max->hugeint[i] + min->hugeint[j] - '0' + carry;
        if(tmp - '9' >0)
        {
            tmp -= 10;
            carry = 1;
        }
        else
            carry = 0;
        hugeint[i] = tmp;
    }
    while(carry&&i>=0)
    {
        char tmp = max->hugeint[i] +1;
        if(tmp -'9'>0)
            tmp -= 10;
        else
            carry = 0;
        hugeint[i--] = tmp;
    }
    if(i==-1 && carry)
    {
        for (i = max->length + 1; i > 0;i--)
            hugeint[i] = hugeint[i - 1];
        hugeint[0] = '1';
    }
    else
        while(i>=0)
        {
            hugeint[i] = max->hugeint[i];
            i--;
        }
    
    return CHugeInt(hugeint);
}
void operator+=(CHugeInt &a, const CHugeInt &b)
{
    a = a + b;
}
ostream &operator<<(ostream &os, const CHugeInt &a)
{
    os << a.hugeint;
    return os;
}
CHugeInt & CHugeInt::operator++()   // 注意这里前置和后置的返回值类型
{
    *this = *this + 1;
    return *this;
}
CHugeInt CHugeInt::operator++(int a)    // 后置需要复制一个原值，然后对原值修改，最后返回原值的拷贝
{
    CHugeInt tmp(*this);
    *this = *this + 1;
    return tmp;
};

int main()
{
    char s[210];
    int n;

    while (cin >> s >> n)
    {
        CHugeInt a(s);
        CHugeInt b(n); //  确实很简化了，因为b是int 总的来说是一个大数加一个普通数 但我就不考虑b是普通数了

        cout << a + b << endl;
        cout << n + a << endl;  // 这里虽然没定义int 和 CHugeInt 类型相加，但是自动把int n 通过类型转换构造函数产生了一个临时对象
        cout << a + n << endl;
        b += n;
        cout << ++b << endl;
        cout << b++ << endl;
        cout << b << endl;
    }
    return 0;
}