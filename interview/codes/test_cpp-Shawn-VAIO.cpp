#include <iostream>
#include <string>
#include <math.h>
#include <glog/logging.h>

using namespace std;

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
