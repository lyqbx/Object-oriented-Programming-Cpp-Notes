// 魔兽世界三(开战)// 魔兽世界之二：装备
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <iterator>dmin
#include <algorithm>
using namespace std;

#define WARRIORSPECIES 5
typedef struct Warrior_info
{
    int health;
    int damage;
    string name;
} warrior_info;

class Warrior;
class Weapon;
class City
{
public:
    int tag;
    static int number;
    static int hour;
    static int min;
    City *city;
    City *prev;
    City *next;
    Warrior *redwarrior = nullptr;
    Warrior *bluewarrior = nullptr;
    Warrior *redtmp = nullptr;
    Warrior *bluetmp = nullptr;
    friend Warrior;
    City();
    void copyWarriors();
    void moveWarriors();
};

class Headquarter : public City
{
public:
    int health;
    int numberofwarriors = 0;
    int status = 1;
    string name;
    int n = 0; // 选择产生的武士
    int tag;
    static int defaulthealth;
    static int numofheadquarter;
    static int activeheadquarters;
    vector<Warrior *> havewarriors;      //类似于City里的w
    vector<warrior_info> warrior_vector; // 存放武士的顺序信息
    Headquarter(string _name);
    bool makewarrior();
    ~Headquarter() {}
};

class Warrior
{
public:
    int tag;
    int health;
    int damage;
    int usewhichweapon = 0;
    int addofweapondamage;
    string name;
    Headquarter *ph;
    City *pc;
    Weapon *pweapon[10] = {0};
    int numberofweapon;
    static int minhealth;
    Warrior(int _tag, Headquarter *_ph, int _health, int _damage, string _name);
    void sortweapon();
    void sortweapon2();
    virtual void specialevent() {}
    void attack(Warrior *t);
    void capture(Warrior *T);
    bool ifdeath();
};

class Dragon : public Warrior
{
public:
    Dragon(int _tag, Headquarter *_ph, int n);
    virtual void specialevent();
    ~Dragon()
    {
            delete this;
    }
};
class Ninja : public Warrior
{
public:
    Ninja(int _tag, Headquarter *_ph, int n);
    virtual void specialevent();
    ~Ninja() {
            delete this;
    }
};
class Iceman : public Warrior
{
public:
    Iceman(int _tag, Headquarter *_ph, int n);
    virtual void specialevent();
    ~Iceman() {
            delete this;
    }
};
class Lion : public Warrior
{
public:
    int loyalty;
    static int k;
    Lion(int _tag, Headquarter *_ph, int n);
    virtual void specialevent();
    ~Lion() { delete this; }
};
class Wolf : public Warrior
{
public:
    Wolf(int _tag, Headquarter *_ph, int n);
    virtual void specialevent();
    ~Wolf() { delete this; }
};

class Weapon
{
public:
    int tag;
    int damage;
    int times = 1;
    string name;
    Warrior *pw;
    static vector<string> weapon_vector;
    Weapon(int _tag, Warrior *_pw);
    virtual void useweapon(Warrior *t) = 0;
};

class Sword : public Weapon
{
public:
    Sword(Warrior *);
    void useweapon(Warrior *t)
    {
        t->health -= damage;
        pw = nullptr;
    }
    ~Sword() { delete this; }
};
class Bomb : public Weapon
{
public:
    Bomb(Warrior *);
    void useweapon(Warrior *t)
    {
        times--;
        t->health -= damage;
        if (pw->name != "ninja")
            pw->health -= damage * 1 / 2;
        pw->addofweapondamage -= damage;
        pw = nullptr;
    }
    ~Bomb() { delete this; }
};
class Arrow : public Weapon
{
public:
    Arrow(Warrior *);
    void useweapon(Warrior *t)
    {
        t->health -= damage;
        if (!--times)
        {
            pw->addofweapondamage -= damage;

            pw = nullptr;
        }
    }
    ~Arrow() { delete this; }
};

City::City()
{
    tag = number;
    number++;
}
void City::copyWarriors()
{
    if (redwarrior)
    {
        if (redwarrior->name == "iceman")
            redwarrior->specialevent();
        redwarrior->pc = next;
        next->redtmp = redwarrior;
        redwarrior = nullptr;
    }
    if (bluewarrior)
    {
        if (bluewarrior->name == "iceman")
            bluewarrior->specialevent();
        bluewarrior->pc = prev;
        prev->bluetmp = bluewarrior;
        bluewarrior = nullptr;
    }
}
void City::moveWarriors()
{
    redwarrior = redtmp;
    bluewarrior = bluetmp;

    if (redwarrior)
    {
        if (next)
        {
            cout << setw(3) << City::hour << ":" << setw(2) << City::min << " red " << redwarrior->name << " " << redwarrior->tag << " marched to city " << redwarrior->pc->tag;
            cout << " with " << redwarrior->health << " elements and force " << redwarrior->damage << endl;
        }
        else
        {
            cout << setw(3) << City::hour << ":" << setw(2) << City::min << " red " << redwarrior->name << " " << redwarrior->tag << " reached blue headquarter ";
            cout << "with " << redwarrior->health << " elements and force " << redwarrior->damage << endl;
        }
    }
    if (bluewarrior)
    {
        if (prev)
        {
            cout << setw(3) << City::hour << ":" << setw(2) << City::min << " blue " << bluewarrior->name << " " << bluewarrior->tag << " marched to city " << bluewarrior->pc->tag;
            cout << " with " << bluewarrior->health << " elements and force " << bluewarrior->damage << endl;
        }
        else
        {
            cout << setw(3) << City::hour << ":" << setw(2) << City::min << " blue " << bluewarrior->name << " " << bluewarrior->tag << " reached red headquarter ";
            cout << "with " << bluewarrior->health << " elements and force " << bluewarrior->damage << endl;
        }
    }
}

Headquarter::Headquarter(string _name) : name(_name)
{
    tag = ++numofheadquarter;
    health = defaulthealth;
    activeheadquarters++;
}
bool Headquarter::makewarrior()
{
    if (warrior_vector[n].health > health)
    {
        if (name == "red")
            redwarrior = nullptr;
        else if (name == "blue")
            bluewarrior = nullptr;
        return false;
    }
    numberofwarriors++;
    cout << setfill('0') << setw(3) << hour << ":" << setw(2) << min << " " << name << " " << warrior_vector[n].name << " " << numberofwarriors << " born" << endl;
    health -= warrior_vector[n].health;
    if (warrior_vector[n].name == "dragon")
    {
        auto a = new Dragon(numberofwarriors, this, n);
        if (name == "red")
            redwarrior = a;
        else
            bluewarrior = a;
        havewarriors.push_back(a);
    }
    else if (warrior_vector[n].name == "ninja")
    {
        auto a = new Ninja(numberofwarriors, this, n);
        havewarriors.push_back(a);
        if (name == "red")
            redwarrior = a;
        else
            bluewarrior = a;
    }
    else if (warrior_vector[n].name == "iceman")
    {
        auto a = new Iceman(numberofwarriors, this, n);
        havewarriors.push_back(a);
        if (name == "red")
            redwarrior = a;
        else
            bluewarrior = a;
    }
    else if (warrior_vector[n].name == "lion")
    {
        auto a = new Lion(numberofwarriors, this, n);
        if (name == "red")
            redwarrior = a;
        else
            bluewarrior = a;
        havewarriors.push_back(a);
    }

    else if (warrior_vector[n].name == "wolf")
    {
        auto a = new Wolf(numberofwarriors, this, n);
        if (name == "red")
            redwarrior = a;
        else
            bluewarrior = a;
        havewarriors.push_back(a);
    }

    n = (n + 1) % WARRIORSPECIES;
    return true;
}

Warrior::Warrior(int _tag, Headquarter *_ph, int _health, int _damage, string _name)
{
    tag = _tag;
    ph = _ph;
    pc = _ph;
    damage = _damage;
    health = _health;
    name = _name;
}

bool myweaponless(Weapon *a, Weapon *b);
bool myweaponless2(Weapon *a, Weapon *b);
void Warrior::sortweapon()
{
    sort(pweapon, pweapon + numberofweapon, myweaponless);
    usewhichweapon = 0;
}
void Warrior::sortweapon2()
{
    sort(pweapon, pweapon + numberofweapon, myweaponless2);
    usewhichweapon = 0;
}

bool Warrior::ifdeath()
{
    if (health <= 0)
    {
        // for (auto i = ph->havewarriors.begin(); i != ph->havewarriors.end(); ++i)
        // {
        //     if ((*i)->tag == tag)
        //     {
        //         ph->havewarriors.erase(i);
        //         break;
        //     }
        // }
        // ph = nullptr;
        name = "died" + name;
        pc = nullptr;
        return true;
    }
    else
        return false;
}

void Warrior::attack(Warrior *t)
{

    if (health > 0 && t->health > 0 && numberofweapon)
    {

        pweapon[usewhichweapon]->useweapon(t);
        if (!pweapon[usewhichweapon]->times)
        {
            for (int j = usewhichweapon; j < numberofweapon; j++)
                pweapon[j] = pweapon[j + 1];
            numberofweapon--;
        }
        // else
        // {
        if (numberofweapon)
            usewhichweapon = (usewhichweapon + 1) % numberofweapon;
        // }
    }
}

void Warrior::capture(Warrior *t)
{
    if (t->numberofweapon)
    {
        while (t->numberofweapon > 0 && numberofweapon < 10)
        {
            t->numberofweapon--;
            pweapon[numberofweapon] = t->pweapon[0];
            pweapon[numberofweapon++]->pw = this;
            t->addofweapondamage -= t->pweapon[0]->damage;
            for (int i = 0; i <= t->numberofweapon; i++)
            {
                t->pweapon[i] = t->pweapon[i + 1];
            }
        }
    }
    if (numberofweapon)
    {
        addofweapondamage = 0;
        for (int i = 0; i < numberofweapon; i++)
        {
            if (pweapon[i]->tag == 0)
                pweapon[i]->damage = damage * 2 / 10;
            else if (pweapon[i]->tag == 1)
                pweapon[i]->damage = damage * 4 / 10;
            else if (pweapon[i]->tag == 2)
                pweapon[i]->damage = damage * 3 / 10;
            addofweapondamage += pweapon[i]->damage;
        }
    }
}

Dragon::Dragon(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].damage, _ph->warrior_vector[n].name)
{
    numberofweapon = 1;
    if (_tag % 3 == 0)
    {
        pweapon[0] = new Sword(this);
    }
    else if (_tag % 3 == 1)
    {
        pweapon[0] = new Bomb(this);
    }
    else if (_tag % 3 == 2)
    {
        pweapon[0] = new Arrow(this);
    }
    addofweapondamage = pweapon[0]->damage;
}

void Dragon::specialevent()
{
    cout << setw(3) << City::hour << ":" << setw(2) << City::min << " " << ph->name << " dragon " << tag << " yelled in city " << pc->tag << endl;
}

Ninja::Ninja(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].damage, _ph->warrior_vector[n].name)
{
    numberofweapon = 2;
    if (_tag % 3 == 0)
    {
        pweapon[0] = new Sword(this);
    }
    else if (_tag % 3 == 1)
    {
        pweapon[0] = new Bomb(this);
    }
    else if (_tag % 3 == 2)
    {
        pweapon[0] = new Arrow(this);
    }
    if ((_tag + 1) % 3 == 0)
    {
        pweapon[1] = new Sword(this);
    }
    else if ((_tag + 1) % 3 == 1)
    {
        pweapon[1] = new Bomb(this);
    }
    else if ((_tag + 1) % 3 == 2)
    {
        pweapon[1] = new Arrow(this);
    }
    addofweapondamage = pweapon[0]->damage + pweapon[1]->damage;
}

void Ninja::specialevent()
{
}

Iceman::Iceman(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].damage, _ph->warrior_vector[n].name)
{
    numberofweapon = 1;
    if (_tag % 3 == 0)
    {
        pweapon[0] = new Sword(this);
    }
    else if (_tag % 3 == 1)
    {
        pweapon[0] = new Bomb(this);
    }
    else if (_tag % 3 == 2)
    {
        pweapon[0] = new Arrow(this);
    };
    addofweapondamage = pweapon[0]->damage;
}

void Iceman::specialevent()
{
    int deletehealth = health * 1 / 10;
    health -= deletehealth;
}

Lion::Lion(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].damage, _ph->warrior_vector[n].name)
{
    numberofweapon = 1;
    loyalty = _ph->health;
    cout << "Its loyalty is " << loyalty << endl;
    numberofweapon = 1;
    if (_tag % 3 == 0)
    {
        pweapon[0] = new Sword(this);
    }
    else if (_tag % 3 == 1)
    {
        pweapon[0] = new Bomb(this);
    }
    else if (_tag % 3 == 2)
    {
        pweapon[0] = new Arrow(this);
    }
    addofweapondamage = pweapon[0]->damage;
}

void Lion::specialevent()
{
    if (loyalty <= 0 && ((ph->name == "red" && pc->tag != (City::number + 1)) || (ph->name == "blue" && pc->tag != 0)))
    {
        cout << setw(3) << City::hour << ":" << setw(2) << City::min << " " << ph->name << " lion " << tag << " ran away" << endl;

        // for (auto i = ph->havewarriors.begin(); i != ph->havewarriors.end(); ++i)
        // {
        //     if ((*i)->tag == tag)
        //     {
        //         ph->havewarriors.erase(i);
        //         break;
        //     }
        // }
        name = "ranawaylion";
        if (ph->name == "red")
        {
            pc->redwarrior = nullptr;
        }
        else if (ph->name == "blue")
        {
            pc->bluewarrior = nullptr;
        }
        pc = nullptr;
    }
    loyalty -= k;
}

Wolf::Wolf(int _tag, Headquarter *_ph, int n) : Warrior(_tag, _ph, _ph->warrior_vector[n].health, _ph->warrior_vector[n].damage, _ph->warrior_vector[n].name)
{
    numberofweapon = 0;
    addofweapondamage = 0;
}

void Wolf::specialevent()
{
    Warrior *tmp = nullptr;
    int weapontag;
    int takenumber = 0;
    if (ph->name == "red")
    {
        tmp = pc->bluewarrior;
    }
    else if (ph->name == "blue")
    {
        tmp = pc->redwarrior;
    }

    if (tmp->name != "wolf" && tmp->numberofweapon > 0 && numberofweapon < 10)
    {
        weapontag = tmp->pweapon[0]->tag;
        while (tmp->numberofweapon > 0 && weapontag == tmp->pweapon[0]->tag && numberofweapon < 10)
        {
            takenumber++;
            tmp->numberofweapon--;
            pweapon[numberofweapon] = tmp->pweapon[0];
            pweapon[numberofweapon++]->pw = this;
            tmp->addofweapondamage -= tmp->pweapon[0]->damage;
            for (int i = 0; i <= tmp->numberofweapon; i++)
            {
                tmp->pweapon[i] = tmp->pweapon[i + 1];
            }
        }

        cout << setw(3) << City::hour << ":" << setw(2) << City::min << " " << ph->name << " wolf " << tag << " took " << takenumber << " " << pweapon[numberofweapon - takenumber]->name;
        cout << " from " << tmp->ph->name << " " << tmp->name << " " << tmp->tag << " in city " << pc->tag << endl;
    }

    if (numberofweapon)
    {
        addofweapondamage = 0;
        for (int i = 0; i < numberofweapon; i++)
        {
            if (pweapon[i]->tag == 0)
                pweapon[i]->damage = damage * 2 / 10;
            else if (pweapon[i]->tag == 1)
                pweapon[i]->damage = damage * 4 / 10;
            else if (pweapon[i]->tag == 2)
                pweapon[i]->damage = damage * 3 / 10;
            addofweapondamage += pweapon[i]->damage;
        }
    }
}

Weapon::Weapon(int _tag, Warrior *_pw)
{
    tag = _tag;
    name = weapon_vector[tag];
    pw = _pw;
}

Sword::Sword(Warrior *_pw) : Weapon(0, _pw)
{
    damage = _pw->damage * 2 / 10;
}
Bomb ::Bomb(Warrior *_pw) : Weapon(1, _pw)
{
    damage = _pw->damage * 4 / 10;
}
Arrow::Arrow(Warrior *_pw) : Weapon(2, _pw)
{
    damage = _pw->damage * 3 / 10;
    times = 2;
}

int Headquarter::defaulthealth = 0;
int Headquarter::numofheadquarter = 0;
int Warrior::minhealth = 1000000000;
int Headquarter::activeheadquarters = 0;
int Lion::k = 0;
int City::hour = 0;
int City::min = 0;
int City::number = 0;
vector<string> Weapon::weapon_vector;

void test();
void setcity(City *, int);

int main()
{
    // freopen("_in.txt", "r", stdin);
    // freopen("_out.txt", "w", stdout);
    Weapon::weapon_vector.push_back("sword");
    Weapon::weapon_vector.push_back("bomb");
    Weapon::weapon_vector.push_back("arrow");
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cout << "Case " << i + 1 << ":" << endl;
        test();
    }
}

void test()
{

    // 初始化
    // M
    cin >> Headquarter::defaulthealth;
    int numberofcity;
    // N
    cin >> numberofcity;
    // K
    cin >> Lion::k;
    // T
    int endtime;
    cin >> endtime;
    City::hour = 0;
    City::min = 0;
    Headquarter::numofheadquarter = 0;
    Headquarter::activeheadquarters = 0;
    Warrior::minhealth = 1000001;
    City::number = 0;
    warrior_info w[WARRIORSPECIES];
    w[0].name = "dragon";
    w[1].name = "ninja";
    w[2].name = "iceman";
    w[3].name = "lion";
    w[4].name = "wolf";
    for (int i = 0; i < WARRIORSPECIES; i++)
    {
        cin >> w[i].health;
        // if (w[i].health < Warrior::minhealth)
        //     Warrior::minhealth = w[i].health;
    }
    for (int i = 0; i < WARRIORSPECIES; i++)
    {
        cin >> w[i].damage;
    }

    Headquarter red("red");
    red.warrior_vector.push_back(w[2]);
    red.warrior_vector.push_back(w[3]);
    red.warrior_vector.push_back(w[4]);
    red.warrior_vector.push_back(w[1]);
    red.warrior_vector.push_back(w[0]);

    City *city = new City[numberofcity];
    setcity(city, numberofcity);

    Headquarter blue("blue");
    blue.warrior_vector.push_back(w[3]);
    blue.warrior_vector.push_back(w[0]);
    blue.warrior_vector.push_back(w[1]);
    blue.warrior_vector.push_back(w[2]);
    blue.warrior_vector.push_back(w[4]);

    blue.prev = &city[numberofcity - 1];
    blue.next = nullptr;
    city[numberofcity - 1].next = &blue;
    City::number -= 2;
    red.prev = nullptr;
    red.next = &city[0];
    city[0].prev = &red;
    bool endofwar = false;

    City *i = &red;
    City *j = &blue;

    // 开始工作
    while (City::hour * 60 + City::min <= endtime && !endofwar)
    {
        if (City::min == 60)
        {
            City::min = 0;
            City::hour++;
        }

        if (City::min == 0)
        {
            red.makewarrior();
            blue.makewarrior();
        }

        if (City::min == 5)
        {
            for (auto i = red.havewarriors.begin(); i != red.havewarriors.end(); ++i)
            {
                if ((*i)->name == "lion")
                {
                    (*i)->specialevent();
                }
            }
            for (auto i = blue.havewarriors.begin(); i != blue.havewarriors.end(); ++i)
            {
                if ((*i)->name == "lion")
                {
                    (*i)->specialevent();
                }
            }
        }

        if (City::min == 10)
        {
            for (auto i = city[0].prev; i != nullptr; i = i->next)
            {
                i->redtmp = nullptr;
                i->bluetmp = nullptr;
            }
            for (auto i = city[0].prev; i != nullptr; i = i->next)
            {
                i->copyWarriors();
            }
            int flag1 = 0;
            int flag2 = 0;
            for (auto i = city[0].prev; i != nullptr; i = i->next)
            {
                i->moveWarriors();
                if (red.bluewarrior && flag1 == 0)
                {
                    cout << setw(3) << City::hour << ":" << setw(2) << City::min;
                    cout << " red headquarter was taken" << endl;
                    endofwar = true;
                    flag1++;
                }
                if (blue.redwarrior && flag2 == 0)
                {
                    cout << setw(3) << City::hour << ":" << setw(2) << City::min;
                    cout << " blue headquarter was taken" << endl;
                    endofwar = true;
                    flag2++;
                }
            }
        }

        if (City::min == 35)
        {
            for (int i = 0; i < numberofcity; ++i)
            {
                if (city[i].redwarrior && city[i].bluewarrior && city[i].redwarrior->name == "wolf")
                {
                    city[i].bluewarrior->sortweapon2();
                    city[i].redwarrior->specialevent();
                }

                if (city[i].bluewarrior && city[i].redwarrior && city[i].bluewarrior->name == "wolf")
                {
                    city[i].redwarrior->sortweapon2();
                    city[i].bluewarrior->specialevent();
                }
            }
        }
        if (City::min == 40)
        {
            for (int i = 0; i < numberofcity; ++i)
            {
                if (city[i].redwarrior && city[i].bluewarrior)
                {

                    if (city[i].tag % 2)
                    {
                        int out = 0;
                        while (city[i].redwarrior->health > 0 && city[i].bluewarrior->health > 0 && (city[i].redwarrior->numberofweapon > 0 || city[i].bluewarrior->numberofweapon > 0))
                        {
                            city[i].redwarrior->attack(city[i].bluewarrior);
                            city[i].bluewarrior->attack(city[i].redwarrior);
                            if (city[i].redwarrior->addofweapondamage + city[i].bluewarrior->addofweapondamage == 0)
                                out++;
                            if (out == 10)
                                break;
                        }
                    }
                    else
                    {
                        int out = 0;
                        while (city[i].redwarrior->health > 0 && city[i].bluewarrior->health > 0 && (city[i].redwarrior->numberofweapon > 0 || city[i].bluewarrior->numberofweapon > 0))
                        {

                            city[i].bluewarrior->attack(city[i].redwarrior);
                            city[i].redwarrior->attack(city[i].bluewarrior);
                            if (city[i].redwarrior->addofweapondamage + city[i].bluewarrior->addofweapondamage == 0)
                                out++;
                            if (out == 10)
                                break;
                        }
                    }
                    if (city[i].redwarrior->health > 0 && city[i].bluewarrior->health <= 0)
                    {
                        cout << setw(3) << City::hour << ":" << setw(2) << City::min << " red " << city[i].redwarrior->name << " ";
                        cout << city[i].redwarrior->tag << " killed blue " << city[i].bluewarrior->name << " " << city[i].bluewarrior->tag;
                        cout << " in city " << city[i].tag << " remaining " << city[i].redwarrior->health << " elements" << endl;
                        if (city[i].redwarrior->name == "dragon")
                            city[i].redwarrior->specialevent();
                        city[i].bluewarrior->sortweapon2();
                        city[i].redwarrior->capture(city[i].bluewarrior);
                    }
                    else if (city[i].bluewarrior->health > 0 && city[i].redwarrior->health <= 0)
                    {
                        cout << setw(3) << City::hour << ":" << setw(2) << City::min << " blue " << city[i].bluewarrior->name << " ";
                        cout << city[i].bluewarrior->tag << " killed red " << city[i].redwarrior->name << " " << city[i].redwarrior->tag;
                        cout << " in city " << city[i].tag << " remaining " << city[i].bluewarrior->health << " elements" << endl;
                        if (city[i].bluewarrior->name == "dragon")
                            city[i].bluewarrior->specialevent();
                        city[i].redwarrior->sortweapon2();
                        city[i].bluewarrior->capture(city[i].redwarrior);
                    }
                    else if (city[i].redwarrior->health > 0 && city[i].bluewarrior->health > 0)
                    {
                        cout << setw(3) << City::hour << ":" << setw(2) << City::min << " both red " << city[i].redwarrior->name << " " << city[i].redwarrior->tag;
                        cout << " and blue " << city[i].bluewarrior->name << " " << city[i].bluewarrior->tag << " were alive in city " << city[i].tag << endl;
                        if (city[i].redwarrior->name == "dragon")
                            city[i].redwarrior->specialevent();
                        if (city[i].bluewarrior->name == "dragon")
                            city[i].bluewarrior->specialevent();
                    }
                    else if (city[i].redwarrior->health <= 0 && city[i].bluewarrior->health <= 0)
                    {
                        cout << setw(3) << City::hour << ":" << setw(2) << City::min << " both red " << city[i].redwarrior->name << " " << city[i].redwarrior->tag;
                        cout << " and blue " << city[i].bluewarrior->name << " " << city[i].bluewarrior->tag << " died in city " << city[i].tag << endl;
                    }
                }
            }
        }
        if (City::min == 50)
        {
            cout << setw(3) << City::hour << ":" << setw(2) << City::min;
            cout << " " << red.health << " elements in red headquarter" << endl;
            cout << setw(3) << City::hour << ":" << setw(2) << City::min;
            cout << " " << blue.health << " elements in blue headquarter" << endl;
        }

        if (City::min == 55)
        {
            for (int i = 0; i < numberofcity; ++i)
            {
                if (city[i].redwarrior)
                {
                    if (city[i].redwarrior->health > 0)
                    {
                        if (city[i].redwarrior->numberofweapon > 0)
                        {
                            int w0 = 0;
                            int w1 = 0;
                            int w2 = 0;
                            city[i].redwarrior->sortweapon();
                            for (int j = 0; j < city[i].redwarrior->numberofweapon; j++)
                            {
                                if (city[i].redwarrior->pweapon[j]->tag == 0)
                                    w0++;
                                else if (city[i].redwarrior->pweapon[j]->tag == 1)
                                    w1++;
                                else if (city[i].redwarrior->pweapon[j]->tag == 2)
                                    w2++;
                            }
                            cout << setw(3) << City::hour << ":" << setw(2) << City::min;
                            cout << " red " << city[i].redwarrior->name << " " << city[i].redwarrior->tag << " has " << w0 << " sword " << w1 << " bomb " << w2 << " arrow and ";
                            cout << city[i].redwarrior->health << " elements" << endl;
                        }
                        else
                        {
                            cout << setw(3) << City::hour << ":" << setw(2) << City::min;
                            cout << " red " << city[i].redwarrior->name << " " << city[i].redwarrior->tag << " has 0 sword 0 bomb 0 arrow and ";
                            cout << city[i].redwarrior->health << " elements" << endl;
                        }
                    }
                    else
                    {
                        city[i].redwarrior = nullptr;
                    }
                }
                if (city[i].bluewarrior)
                    if (city[i].bluewarrior->health > 0)
                    {
                        if (city[i].bluewarrior->numberofweapon > 0)
                        {
                            int w0 = 0;
                            int w1 = 0;
                            int w2 = 0;
                            city[i].bluewarrior->sortweapon();
                            for (int j = 0; j < city[i].bluewarrior->numberofweapon; j++)
                            {
                                if (city[i].bluewarrior->pweapon[j]->tag == 0)
                                    w0++;
                                else if (city[i].bluewarrior->pweapon[j]->tag == 1)
                                    w1++;
                                else if (city[i].bluewarrior->pweapon[j]->tag == 2)
                                    w2++;
                            }
                            cout << setw(3) << City::hour << ":" << setw(2) << City::min;
                            cout << " blue " << city[i].bluewarrior->name << " " << city[i].bluewarrior->tag << " has " << w0 << " sword " << w1 << " bomb " << w2 << " arrow and ";
                            cout << city[i].bluewarrior->health << " elements" << endl;
                        }
                        else
                        {
                            cout << setw(3) << City::hour << ":" << setw(2) << City::min;
                            cout << " blue " << city[i].bluewarrior->name << " " << city[i].bluewarrior->tag << " has 0 sword 0 bomb 0 arrow and ";
                            cout << city[i].bluewarrior->health << " elements" << endl;
                        }
                    }
                    else
                    {
                        city[i].bluewarrior = nullptr;
                    }
            }
        }
        City::min += 5;
    }
    delete[] city;
}
void setcity(City *city, int n)
{
    for (int i = 0; i < n - 1; i++)
        city[i].next = &city[i + 1];
    for (int i = n - 1; i > 0; i--)
        city[i].prev = &city[i - 1];
}

bool myweaponless(Weapon *a, Weapon *b)
{
    if (a->tag < b->tag || a->tag == b->tag && a->times < b->times)
        return true;
    else
    {
        return false;
    }
}
bool myweaponless2(Weapon *a, Weapon *b)
{
    if (a->tag < b->tag || a->tag == b->tag && a->times > b->times)
        return true;
    else
    {
        return false;
    }
}