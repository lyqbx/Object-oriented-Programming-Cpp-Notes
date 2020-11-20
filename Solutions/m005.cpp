// 学生信息处理程序
/*
输入
输入数据为一行，包括：
姓名,年龄,学号,第一学年平均成绩,第二学年平均成绩,第三学年平均成绩,第四学年平均成绩。
其中姓名为由字母和空格组成的字符串（输入保证姓名不超过20个字符，并且空格不会出现在字符串两端），年龄、学号和学年平均成绩均为非负整数。信息之间用逗号隔开。
输出
输出一行数据，包括：
姓名,年龄,学号,四年平均成绩。
信息之间用逗号隔开
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student
{
private:
    char name[20];
    int age;
    int snum;
    double scores[4];
    double avg;

public:
    void input(){
        char buf[210];
        cin.getline(buf,200);
        char *p = strtok(buf, ","); // 对char * 按 const char * 中分隔符逐个抽取，第一次char * 填目标字符串，后续调用填NULL
        strcpy(name, p);
        p = strtok(NULL, ",");
        age = atoi(p);
        p = strtok(NULL, ",");
        snum = atoi(p);
        for (int i = 0; i < 4;i++){
            p = strtok(NULL, ",");
            scores[i] = atoi(p);
        }
    }
    double calculate(){
        double returnavg = 0;
        for (int i = 0; i < 4;i++){
            returnavg += (scores[i] / 4);
        }
        return returnavg;
    }
    void output(){
        cout << name << "," << age << "," << snum << "," << calculate() << endl;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
    system("pause");
    return 0;
}