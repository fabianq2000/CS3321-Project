#include "RegisteredUser.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

static ofstream out;//object for output
static ifstream in;//object for input

void RegisteredUser::addUser(string a, string b, string c, string d, string e)
{
	out.open("usersdb.txt", ios::app);
	out << "Username: " << a << endl;
	out << "Password: " << b << endl;
	out << "First Name: " << c << endl;
	out << "Last Name :" << d << endl;
	out << "Email :" << e << endl;
	out << "----------" << endl;
	out.close();
}
//==============================================
/*string RegisteredUser::getPasswordHash(string a)
{
	in.open("usersdb.txt");
	string line;
	while (in >> line)
	{

	}
	in.close();
}*/
//===========================================
//void RegisteredUser::updatePassword()
//{

//}