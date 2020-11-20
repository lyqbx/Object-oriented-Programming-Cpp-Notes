// 热血格斗场
#include <iostream>
#include <set>
using namespace std;

struct vip
{
    int id;
    int ability;
    vip(int i, int j) : id(i), ability(j) {}
    friend bool operator<(const vip &a, const vip &b);
};

bool operator<(const vip &a, const vip &b)
{
    return a.ability < b.ability;
}
int main()
{

    //     freopen("_in.txt", "r", stdin);
    // freopen("_out.txt", "w", stdout);
    set<vip> v;
    v.insert(vip(1, 100000000));
    int n;
    int newid, newability;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> newid >> newability;
        auto a = v.insert(vip(newid, newability)).first;
        cout << newid << " ";
        auto e = v.end();
        e--;
        if (a == v.begin())
        {
            auto b = a;
            b++;
            cout << b->id << endl;
        }
        else
        {
            auto b = a;
            b--;
            auto c = a;
            c++;
            if (newability - b->ability <= c->ability - newability)
                cout << b->id;
            else
                cout << c->id;
            cout << endl;
        }

    }

}