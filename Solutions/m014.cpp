// MyString
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
	void Copy(const char * s){
			p = new char[strlen(s) + 1];
			strcpy(p, s);
	}
	MyString(const char *& s){
			p = new char[strlen(s) + 1];
			strcpy(p,s);


	}
	friend ostream &operator<<(ostream &,const MyString&);
	MyString & operator=(const MyString &);
	MyString & operator=(char * );

};
ostream & operator<<(ostream & o,const MyString & str)
{
	o << str.p;
	return o;
    
}

MyString & MyString::operator=(char *a){

			p = new char[strlen(a) + 1];
			strcpy(p,a);
		return *this;
		
}
MyString & MyString::operator=(const MyString &a){
			p = new char[strlen(a.p) + 1];
			strcpy(p,a.p);
		return *this;
		
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;
		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}