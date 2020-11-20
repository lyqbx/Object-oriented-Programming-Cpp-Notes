// Set
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    // freopen("_in.txt", "r", stdin);
    // freopen("_out.txt", "w", stdout);
    multiset<int> se;
    set<int> ad;
    int n;
    cin >> n;
    string command;
    int num;
    while (n--)
    {
        cin >> command >> num;
        if (command == "add")
        {
            se.insert(num);
            ad.insert(num);
            cout << se.count(num) << endl;
        }
        else if (command == "ask")
        {
            if (ad.count(num) == 0)
            {
                cout << 0 << " " << se.count(num);
            }
            else
                cout << 1 << " " << se.count(num);
            cout << endl;
        }
        else if (command == "del")
        {
            cout << se.count(num) << endl;
            se.erase(num);
        }
    }
}