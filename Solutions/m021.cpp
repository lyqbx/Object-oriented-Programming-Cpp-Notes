// 魔兽世界之二：装备
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;

#define WARRIORSPECIES 5

typedef struct Warrior_info
{
    int health;
    string name;
    int number = 0;
} warrior_info;

class Weapon;
class Headquarter;

class Warrior
{
private:
    int tag;
    int health;
    string species;
    Headquarter *ph;

public:
    static int minhealth;
    Warrior(int _tag, Headquarter *_ph, int _health, string _species);
};
class Dragon : public Warrior
{
private:
    Weapon *pweapon;
    double morale;

public:
    Dragon(int _tag, Headquarter *_ph, int n);
    ~Dragon();
};
class Ninja : public Warrior
{
private:
    Weapon *pweapon1 = 0, *pweapon2 = 0;

public:
    Ninja(int _tag, Headquarter *_ph, int n);
    ~Ninja();
};
class Iceman : public Warrior
{
private:
    Weapon *pweapon = 0;

public:
    Iceman(int _tag, Headquarter *_ph, int n);
    ~Iceman();
};
class Lion : public Warrior
{
private:
    int loyalty;

public:
    Lion(int _tag, Headquarter *_ph, int n);
};
class Wolf : public Warrior
{
public:
    Wolf(int _tag, Headquarter *_ph, int n);
};

class Weapon
{
private:
    int tag;
    int damage;
    string name;
    Warrior *pwarrior;

public:
    string getname() { return name; }
    static vector<string> weapon_vector;
    Weapon(int _tag, int _damage, Warrior *_pwarrior);
};
// class Sword : public Weapon
// {
// };
// class Bomb : public Weapon
// {
// };
// class Arrow : public Weapon
// {
// };

class Headquarter
{
private:
    int tag;
    int health;
    int numberofwarriors = 0;
    int status = 1;
    vector<Warrior *> w;
    string name;
    int n = 0; // 选择产生的武士
public:
    static int defaulthealth;
    static int numofheadquarter;
    static int thetime;
    static int activeheadquarters;
    friend Warrior;
    vector<warrior_info> warrior_vector;
    int gethealth() { return health; }
    Headquarter(string _name);

    void pushtime();

    void stopmaking();
    void makewarrior();
    ~Headquarter();
};
Warrior::Warrior(int _tag, Headquarter *_ph, int _health, string _species)
{
    tag = _tag;
    ph = _ph;
    health = _health;
    species = _species;
}
Dragon::Dragon(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].name)
{
    pweapon = new Weapon(_tag % 3, 0, this);
    morale = double(_ph->gethealth()) / double(_ph->warrior_vector[n].health);
    cout << "It has a " << pweapon->getname() << ",and it's morale is " << fixed << setprecision(2) << morale << endl;
}
Dragon::~Dragon()
{
    if (pweapon)
        delete pweapon;
}
Ninja::Ninja(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].name)
{
    pweapon1 = new Weapon(_tag % 3, 0, this);
    pweapon2 = new Weapon((_tag + 1) % 3, 0, this);
    cout << "It has a " << pweapon1->getname() << " and a " << pweapon2->getname() << endl;
}
Ninja::~Ninja()
{
    if (pweapon1)
        delete pweapon1;
    if (pweapon2)
        delete pweapon2;
}
Iceman::Iceman(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].name)
{
    pweapon = new Weapon(_tag % 3, 0, this);
    cout << "It has a " << pweapon->getname() << endl;
}
Iceman::~Iceman()
{
    if (pweapon)
        delete pweapon;
}
Lion::Lion(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].name)
{
    loyalty = _ph->gethealth();
    cout << "It's loyalty is " << loyalty << endl;
}
Wolf::Wolf(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].name)
{
}

Weapon::Weapon(int _tag, int _damage, Warrior *_pwarrior)
{
    tag = _tag;
    name = weapon_vector[tag];
    pwarrior = _pwarrior;
}
Headquarter::Headquarter(string _name) : name(_name)
{
    tag = ++numofheadquarter;
    health = defaulthealth;
    activeheadquarters++;
}
void Headquarter::pushtime()
{
    if (tag == numofheadquarter)
        thetime++;
}
void Headquarter::stopmaking()
{
    if (!status)
    {
        activeheadquarters--;
        cout << setfill('0') << setw(3) << thetime << " " << name << " headquarter stops making warriors" << endl;
        status = -1;
    }
    pushtime();
}
void Headquarter::makewarrior()
{
    if (status == 1)
    {
        if (Warrior::minhealth > health)
        {
            status = 0;
            stopmaking();
            return;
        }
        while (warrior_vector[n].health > health)
        {
            n = (n + 1) % WARRIORSPECIES;
        }
        warrior_vector[n].number++;
        numberofwarriors++;
        cout << setfill('0') << setw(3) << thetime << " " << name << " " << warrior_vector[n].name << " " << numberofwarriors << " born with strength " << warrior_vector[n].health << ",";
        cout << warrior_vector[n].number << " " << warrior_vector[n].name << " in " << name << " headquarter" << endl;
        health -= warrior_vector[n].health;
        if (warrior_vector[n].name == "dragon")
            w.push_back(new Dragon(numberofwarriors, this, n));
        else if (warrior_vector[n].name == "ninja")
            w.push_back(new Ninja(numberofwarriors, this, n));
        else if (warrior_vector[n].name == "iceman")
            w.push_back(new Iceman(numberofwarriors, this, n));
        else if (warrior_vector[n].name == "lion")
            w.push_back(new Lion(numberofwarriors, this, n));
        else if (warrior_vector[n].name == "wolf")
            w.push_back(new Wolf(numberofwarriors, this, n));

        n = (n + 1) % WARRIORSPECIES;
    }
    pushtime();
}
Headquarter::~Headquarter()
{
    for (int i = 0; i < numberofwarriors; i++)
    {
        delete w[i];
    }
}



 int Headquarter::defaulthealth = 0;
 int Headquarter::numofheadquarter = 0;
 int Headquarter::thetime = 0;
 int Warrior::minhealth = 1000000000;
 int Headquarter::activeheadquarters = 0;
 vector<string> Weapon:: weapon_vector;

void test()
{
    cin >> Headquarter::defaulthealth;
    Headquarter::thetime = 0;
    Headquarter::numofheadquarter = 0;
    Headquarter::activeheadquarters = 0;
    Warrior::minhealth = 1000000000;
    warrior_info w[WARRIORSPECIES];
    w[0].name = "dragon";
    w[1].name = "ninja";
    w[2].name = "iceman";
    w[3].name = "lion";
    w[4].name = "wolf";
    for (int i = 0; i < WARRIORSPECIES; i++)
    {
        cin >> w[i].health;
        if (w[i].health < Warrior::minhealth)
            Warrior::minhealth = w[i].health;
    }

    Headquarter red("red");

    red.warrior_vector.push_back(w[2]);
    red.warrior_vector.push_back(w[3]);
    red.warrior_vector.push_back(w[4]);
    red.warrior_vector.push_back(w[1]);
    red.warrior_vector.push_back(w[0]);

    Headquarter blue("blue");
    blue.warrior_vector.push_back(w[3]);
    blue.warrior_vector.push_back(w[0]);
    blue.warrior_vector.push_back(w[1]);
    blue.warrior_vector.push_back(w[2]);
    blue.warrior_vector.push_back(w[4]);
    while (Headquarter::activeheadquarters)
    {
        red.makewarrior();
        blue.makewarrior();
    }
};

int main()
{
    Weapon::weapon_vector.push_back("sword");
    Weapon::weapon_vector.push_back("bomb");
    Weapon::weapon_vector.push_back("arrow");

    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cout << "Case:" << i + 1 << endl;
        test();
    }
}
