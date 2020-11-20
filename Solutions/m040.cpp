// List
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{

    string s;
    int n;
    string command;
    int num1, num2;
    list<int> *l = new list<int>[5001];
    int size = 5001;
    int length = 0;
    vector<int> nums;
    // freopen("_in.txt", "r", stdin);
    // freopen("_out.txt", "w", stdout);
    cin >> n;
    cin.get();
    while (n--)
    {
        getline(cin, s);
        istringstream inputString(s);
        inputString >> command;
        if (command == "new" || command == "out" || command == "unique")
            inputString >> num1;
        else if (command == "add" || command == "merge")
            inputString >> num1 >> num2;
        else
        {
            cerr << "输入错误" << endl;
        }
        if (command == "new")
        {
            // if (length == size-1)
            // {
            //     size += 100;
            //     list<int> *tmp = new list<int>[size];
            //     for (int i = 0; i < size - 5; i++)
            //         *tmp = *l;
            //     delete[] l;
            //     l = tmp;
            // }
            nums.push_back(num1);
            length++;
        }
        else if (command == "add")
        {
            // int i = *(find(nums.begin(), nums.end(), num1));
            l[num1-1].push_back(num2);
        }
        else if (command == "out")
        {
            // int i = *(find(nums.begin(), nums.end(), num1));
            list<int> tmp1 = l[num1-1];
            tmp1.sort();
            for (list<int>::iterator a = tmp1.begin(); a != tmp1.end(); ++a)
            {
                cout << *a << " ";
            }
            cout << endl;
        }
        else if (command == "merge")
        {
            // int i1 = *(find(nums.begin(), nums.end(), num1));
            // int i2 = *(find(nums.begin(), nums.end(), num2));
            l[num1-1].merge(l[num2-1]);
        }
        else if (command == "unique")
        {
            // int i = *(find(nums.begin(), nums.end(), num1));
            l[num1-1].sort();
            l[num1-1].unique();
        }
    }
}