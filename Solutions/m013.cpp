// 魔兽世界之一：备战 先不用多态写了，毕竟这时候还没学多态
#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

#define NUMBER_OF_WIRRIOR_KINDS 5
#define MAX 999999

class Warrior
{
private:
    char kindofwarrior[10];    // 当前武士种类
    int life;   // 这个种类的生命值
    int numberofthiskind;   //这种有多少个武士
    // HeadQuarter *headquarter;   // 这个武士的主人
    static int minlife;

public:
    friend class HeadQuarter;
    int &inputlife();
    static int &inputminlife() { return minlife; }
    char *getkindofwarrior();
    Warrior( char *kind,int lif ,int number);
    ~Warrior();

};


Warrior::Warrior( char *kind,int lif = 0,int number = 0)
{
    strcpy(kindofwarrior, kind);
    life = lif;
    numberofthiskind = number;
}

Warrior::~Warrior()
{
    minlife = MAX;
}

int &Warrior::inputlife()  {  return life;}
char *Warrior::getkindofwarrior()  { return kindofwarrior; }

class HeadQuarter
{
private:
    static int defaultlifemoney;    // 初始生命元
    int lifemoney;  // 当前生命元
    char name[10] ;   //名字
    char warriororder[NUMBER_OF_WIRRIOR_KINDS][10]; //保存这个司令部产生武士的顺序
    static int numberofhq;  //司令部的总数
    static int time ;   //当前时间
    int order;  // 当前对象司令部的编号
    int status; //状态，用来判断是否产生武士
    int whichwarrior; //判断产生哪个武士
    int numberofwarriors; //武士数量

public:
    Warrior *warriors[NUMBER_OF_WIRRIOR_KINDS]; //一个司令部的武士
    HeadQuarter( const char *thename,const char *theorder[]);
    ~HeadQuarter();
    static int &gettime() { return time; }
    int &getstatus() { return status; }
    static int &getdefaultlifemoney() { return defaultlifemoney; }
    char *getname() { return name; }
    int &getlife() { return lifemoney; }
    void makewarrior();
    void stopmakewarrior();

};

HeadQuarter::HeadQuarter( const char *thename,const char *theorder[])
{
    strcpy(name, thename);

    for (int i = 0; i < NUMBER_OF_WIRRIOR_KINDS;i++)
        strcpy(warriororder[i], theorder[i]);

    lifemoney = defaultlifemoney;
    order = ++numberofhq;
    status = 1;
    whichwarrior = 0;
    numberofwarriors = 0;
}

HeadQuarter::~HeadQuarter()
{
    time = 0;
    numberofhq = 0;
}

void HeadQuarter::makewarrior()
{
    if(Warrior::minlife > lifemoney) {
        status = 0;
        HeadQuarter::stopmakewarrior();
    }
    else
    {

        int i;
        char *thiswarrior = warriororder[whichwarrior];
        for (i = 0; (i < NUMBER_OF_WIRRIOR_KINDS) && strcmp(thiswarrior,warriors[i]->kindofwarrior);i++)
            ;
        if(warriors[i]->life <= lifemoney)
        {
            warriors[i]->numberofthiskind++;
            cout <<setw(3)<<setfill('0') << time << " "<< name << " "<< warriors[i]->kindofwarrior << " ";
            cout << ++numberofwarriors << " born with strength " << warriors[i]->life;
            cout << "," << warriors[i]->numberofthiskind << " " << warriors[i]->kindofwarrior;
            cout << " in " << name << " headquarter" << endl;
            lifemoney -= warriors[i]->life;
            whichwarrior = (whichwarrior + 1) % NUMBER_OF_WIRRIOR_KINDS;
        }
        else
        {
            whichwarrior = (whichwarrior + 1) % NUMBER_OF_WIRRIOR_KINDS;
            HeadQuarter::makewarrior();
        } 
    }

}

void HeadQuarter::stopmakewarrior()
{
cout << setw(3)<<setfill('0') << time << " " << name << " headquarter stops making warriors" << endl;
}
int HeadQuarter::numberofhq = 0;
int HeadQuarter::time = 0;
int HeadQuarter::defaultlifemoney = 0;
int Warrior::minlife = MAX;

void test(int k)
{
    Warrior r1("dragon"), r2("ninja"), r3("iceman"), r4("lion"), r5("wolf");
    Warrior b1("dragon"), b2("ninja"), b3("iceman"), b4("lion"), b5("wolf");
    const char *ra[10] = {"iceman", "lion", "wolf", "ninja", "dragon"};
    const char *ba[10] = {"lion", "dragon", "ninja", "iceman", "wolf"};
    HeadQuarter r("red",ra), b("blue",ba);
    r.warriors[0] = &r1;b.warriors[0] = &b1;
    r.warriors[1] = &r2;b.warriors[1] = &b2;
    r.warriors[2] = &r3;b.warriors[2] = &b3;
    r.warriors[3] = &r4;b.warriors[3] = &b4;
    r.warriors[4] = &r5;b.warriors[4] = &b5;
        int warriorlife;
        cin >> HeadQuarter::getdefaultlifemoney(); // 输入司令部生命元
        r.getlife() = b.getlife() = HeadQuarter::getdefaultlifemoney();

        for (int i = 0; i < 5;i++)  // 输入每种武士的生命值
        {
            cin >> warriorlife;
            if(warriorlife < Warrior::inputminlife())
                Warrior::inputminlife() = warriorlife;
            r.warriors[i]->inputlife() = b.warriors[i]->inputlife() = warriorlife;
        }
        cout << "Case:" << k << endl;
        while(r.getstatus()||b.getstatus())
        {
                if(r.getstatus())
                    r.makewarrior();
                if(b.getstatus())
                    b.makewarrior();
            HeadQuarter::gettime()++;
        }
}

int main()
{
    int n;
    cin >> n;
    for (int k = 1; k <= n; k++)
    {
        test(k);
    }
}