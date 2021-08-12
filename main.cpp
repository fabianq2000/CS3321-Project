#include <iostream>
#include <string>
#include <fstream>
#include "LoginUser.h"
#include "RegisteredUser.h"
#include "EbookTesting.cpp"
using namespace std;

int main() {
	EbookTesting e;
	e.testEbook();

	return 0;
}

//ofstream box;//object for output

/*int main()
{
	RegisteredUser info;

	info.setUserName();
	info.setUserPassword();
	info.setFirstName();
	info.setLastName();
	info.setEmail();

	info.encryptPassword();
	//bool result = info.authenticate();
	info.addNewUser();


	system("pause");
	return 0;
}*/