// 山寨版istream_iterator
#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
    // 在此处补充你的代码
private:
    T *beginn;
    T *n;
    istream &is;

public:
    CMyistream_iterator(istream &_is) : is(_is)
    {
        beginn = new T[100];
        n = beginn;
        is >> *n;
    }
    T operator*() { return (*n); }
    CMyistream_iterator operator++(int s)
    {
        n++;
        is >> *n;
        return *this;
    }
    // ~CMyistream_iterator()
    // {
    //     if(beginn!=nullptr)
    //         delete [] beginn;
    // }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        CMyistream_iterator<int> inputInt(cin);
        int n1, n2, n3;
        n1 = *inputInt; //读入 n1
        int tmp = *inputInt;
        cout << tmp << endl;
        inputInt++;
        n2 = *inputInt; //读入 n2
        inputInt++;
        n3 = *inputInt; //读入 n3
        cout << n1 << " " << n2 << " " << n3 << " ";
        CMyistream_iterator<string> inputStr(cin);
        string s1, s2;
        s1 = *inputStr;
        inputStr++;
        s2 = *inputStr;
        cout << s1 << " " << s2 << endl;
    }
    return 0;
}