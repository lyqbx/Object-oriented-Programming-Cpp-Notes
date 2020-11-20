// 全面的MyString
#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char *s)
{
    int i = 0;
    for (; s[i]; ++i)
        ;
    return i;
}
void strcpy(char *d, const char *s)
{
    int i = 0;
    for (i = 0; s[i]; ++i)
        d[i] = s[i];
    d[i] = 0;
}
int strcmp(const char *s1, const char *s2)
{
    for (int i = 0; s1[i] && s2[i]; ++i)
    {
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}
void strcat(char *d, const char *s)
{
    int len = strlen(d);
    strcpy(d + len, s);
}
class MyString
{
    // 在此处补充你的代码
private:
    char *str;

public:
    MyString() : str(new char[1]) { str[0] = '\0'; }
    MyString(const char *s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    MyString(const MyString &s)
    {
        if(this == &s)
            delete[] str;
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);

    }
    ~MyString() { delete[] str; }
    bool operator<(const MyString &s)
    {
        if (strcmp(this->str, s.str) == -1)
            return true;
        else
            return false;
    }
    bool operator==(const MyString &s)
    {
        return !strcmp(this->str, s.str);
    }
    bool operator>(const MyString &s)
    {
        if (strcmp(this->str, s.str) == 1)
            return true;
        else
            return false;
    }
    char &operator[](int i)
    {
        return str[i];
    }
    friend MyString operator+(const MyString &a, const MyString &b);
    MyString &operator=(const MyString &s)
    {
        if(this == &s)
            return *this;
        delete[] str;
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
        return *this;
    }
    MyString &operator+=(const MyString &s)
    {
        *this = *this + s;
        return *this;
    }
    MyString operator()(int a,int b)
    {
        char *tmp = new char[b + 1];
        for (int i = a, j = 0; j < b;i++,j++)
        {
            tmp[j] = str[i];
        }
        tmp[b] = '\0';
        return MyString(tmp);
    }
    friend ostream &operator<<(ostream &os, const MyString &s);
};

MyString operator+(const MyString &a,const MyString & b)
{
    char *tmp = new char[strlen(a.str) + strlen(b.str) + 1];
    strcpy(tmp, a.str);
    strcat(tmp, b.str);
    return MyString(tmp);
}
ostream &operator<<(ostream &os,const MyString &s)
{
    os << s.str;
    return os;
};
int CompareString(const void *e1, const void *e2)
{
    MyString *s1 = (MyString *)e1;
    MyString *s2 = (MyString *)e2;
    if (*s1 < *s2)
        return -1;
    else if (*s1 == *s2)
        return 0;
    else if (*s1 > *s2)
        return 1;
    return 0;
}
int main()
{
    MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
    MyString SArray[4] = {"big", "me", "about", "take"};
    cout << "1. " << s1 << s2 << s3 << s4 << endl;
    s4 = s3;
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[2] = 'A';
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray, 4, sizeof(MyString), CompareString);
    for (int i = 0; i < 4; i++)
        cout << SArray[i] << endl;
    //s1的从下标0开始长度为4的子串
    cout << s1(0, 4) << endl;
    //s1的从下标5开始长度为10的子串
    cout << s1(5, 10) << endl;
    return 0;
}