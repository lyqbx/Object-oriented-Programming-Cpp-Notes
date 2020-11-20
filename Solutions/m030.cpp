// 你真的搞清楚为啥while(cin>>n)能成立了吗？
// 要求读入-1就停
#include <iostream>
using namespace std;
class MyCin
{
    int status = 1;
public:
    MyCin & operator>>(int &n)
    {
        int tmp = n;
        cin >> n;
        if(n == -1){
            n = tmp;
            status = 0;
        }
        return *this;
    }
    operator bool() { return status; }
};


int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}
