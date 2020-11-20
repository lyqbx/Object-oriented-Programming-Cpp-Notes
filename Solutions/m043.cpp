// 冷血格斗场
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
    if (a.ability == b.ability)
        return a.id < b.id;
    return a.ability < b.ability;
}
int main()
{

    // freopen("_in.txt", "r", stdin);
    // freopen("_out.txt", "w", stdout);
    set<vip> v;
    v.insert(vip(1, 100000000));
    int n;
    int newid, newability;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> newid >> newability;

        auto min = v.lower_bound(vip(0, newability)); // 有相同值时，或者比他大的
        auto a = v.insert(vip(newid, newability)).first;
        cout << newid << " ";
        if (a == v.begin() || min->ability == newability || min->ability - newability < newability - (--a)->ability)
            cout << min->id;
        else if(min->ability - newability == newability - a->ability)
        {
            auto a2 = v.lower_bound(vip(0, a->ability));
            if(a2->id < min->id)
                cout << a2->id;
            else
            {
                cout << min->id;
            }
            
        }
        else{
           auto a2 = v.lower_bound(vip(0, a->ability)); 
           cout << a2->id;
        }
        cout << endl;
    }
}