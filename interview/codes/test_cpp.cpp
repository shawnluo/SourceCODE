#include <iostream>
#include <string>
#include <math.h>
#include <glog/logging.h>

#define test

using namespace std;

#if defined test

class Fish
{
protected:
//private:
	bool FreshWaterFish;

public:
	int x = 0;
	void Swim()
	{
		cout << FreshWaterFish << endl;
	}
};

class Tuna: public Fish
{
public:
	Tuna()
	{
		FreshWaterFish = false;
	}
};


int main(void)
{
	Tuna myDinner;
	myDinner.Swim();
	myDinner.x = 100;
//	myDinner.FreshWaterFish = 1;
	return 0;
}


#elif defined yy
int main(int argc, char *argv[])
{
/*
	string Greetings ("Hello std::string!");
//	cout << Greetings << endl;

	string all = Greetings + "good";
	cout << all << " " << all.length() << endl;

	Greetings[3] = '\0';
	cout << Greetings << " " << all.length() << endl;
*/
	int num[5] = {0};
	num[5] = pow(2, 16);

//	unsigned int x = pow(2, 16);
	cout << num[5] << endl;
	return 0;
}

#include<iostream>
using namespace std;

int public_dataX;

class X
{
private:
	int private_dataX;
protected:
	int protected_dataX;
public:
	int public_dataX;
	int cc(int x);
	
	X operator+(const X &b)
	{
		X box;
		box.public_dataX= this->public_dataX + b.private_dataX;

		return box;
	}
};

int X::cc(int x)
{
	return ::public_dataX;
}

class A :public X
{
public:	
/*	int a_var;
	int add(int a);
	int add(int a, int b);*/
	void funct()
	{
		int a;
//		a = private_dataX;
		a = protected_dataX;
		a = public_dataX;
	}
};

/*
int A::add(int a)
{
	return a + ::a_var;
}

int A::add(int a, int b)
{
	return a + b;
}
*/
int main(void)
{
	int x;

	A objA;
	
	x = objA.public_dataX;
//	x = objA.private_dataX;
	
	return 0;
}

#elif defined xx

#include<iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////
class X       //parent class
{
private:
    int private_dateX;
protected:
    int protected_dateX;
public:
    int public_dateX;
};
//////////////////////////////////////////////////////////////////////////
class A :public X      //derive class B from base class A (shared inheritance)
{
public:
    void funct()
    {
        int a;
        a = private_dataX;   //error: the privated member of base class is invisible in derive class
        a = protected_dataX; //ok: the protected member of base class is protected member in derive class
        a = public_dataX;    //ok: the public member of base class is public member in derive class
    }
};
//////////////////////////////////////////////////////////////////////////
class B :private X  //derive class C from base class A(privated inheritance)
{
public:
    void funct()
    {
        int b;
        b = private_dataX;    //error: the privated member of base class is invisible in derive class 
        b = protected_dataX;  //ok: the protected member of base class is privated member in derive class
        b = public_dataX;     //ok: the public member of base class is privated member in derive class
    }
};
//////////////////////////////////////////////////////////////////////////
class C :protected X   //derive class D from base class A (protectd inheritance)
{
public:
    void funct()
    {
        int c;
        c = private_dataX;   //error: the privated member of base class is invisible in derive class
        c = protected_dataX; //ok: the protected member of base class is privated member in derive class
        c = public_dataX;    //ok: the public member of base class is protectd member in derive class
    }
};
//////////////////////////////////////////////////////////////////////////
int main()
{
    int x;
 
    A objA;
    x = objA.private_dataX;   //error: 基类中私有成员在派生类中是不可见的，对对象不可见
    x = objA.protected_dataX; //error: 基类的保护成员在派生类中为保护成员，对对象不可见
    x = objA.public_dataX;    //ok: 基类的公共成员在派生类中为公共成员，对对象可见
 
    B objB;
    x = objB.private_dataX;   //error: 基类中私有成员在派生类中是不可见的，对对象不可见
    x = objB.protected_dataX; //error: 基类的保护成员在派生类中为私有成员，对对象不可见
    x = objB.public_dataX;    //error: 基类的公共成员在派生类中为私有成员，对对象不可见
 
    C objC;
    x = objC.private_dataX;   //error: 基类中的私有成员在派生类中是不可见的，对对象不可见
    x = objC.protected_dataX; //error: 基类的保护成员在拍摄各类中是保护成员，对对象不可见
    x = objC.public_dataX;    //error: 基类的公共成员在派生类中为保护成员，对对象不可见
 
    return 0;
}


#include <vector>
#include <iostream>

using namespace std;

class Base
{
public:
    Base(const char* name);
    // warning! the destructor should be virtual
    ~Base();

    virtual void doStuff();
private:
    const char* m_name;
};

Base :: Base(const char* name) : m_name(name)
{

}

Base :: ~Base()
{

}



void Base :: doStuff()
{
    cout << "Doing stuff in Base" << endl;
}



class Derived : public Base
{
public:
    Derived(const char* name);
    ~Derived();

virtual void doStuff();
private:
    vector<int>* m_charCodes;
};

Derived :: Derived(const char* name) : Base(name)
{
    m_charCodes = new vector<int>;
} 

Derived :: ~Derived()
{
    delete m_charCodes;
}

void Derived :: doStuff() 
{
    cout << "Doing stuff in Derived" << endl;
}

int main(int argc, char* argv[])
{
    // assign the derived class object pointer to
    // the base class pointer
    char* theName = "Some fancy name";
    Base* b = new Derived(theName);

    // do some computations and then delete the
    // pointer
    delete b;
    return 0;
}
#endif
