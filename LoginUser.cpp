#include "LoginUser.h"
#include "RegisteredUser.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

static ifstream in;

void LoginUser::setUserName()
{
	bool check = true;
	while (check)//loop breaks if check is false
	{
		cout << "Enter username: ";
		getline(cin, userName);

		in.open("usersdb.txt", ios::in);

		string line;
		string line2;
		while (getline(in, line))//loop to check if username exists already
		{
			line2 = line.substr(0, 10);
			if (line2 == "Username: ")
			{
				line2 = line.substr(10, userName.length());
				if (userName == line2)
				{
					cout << "Username already exists" << endl;
					cout << "Try a different username" << endl;
					break;
					
				}
				
			}
			
		}
		
	}
	in.close();
}
//=======================================================
void LoginUser::setUserPassword()
{
	string CP; //to compare if its same password from first time
	bool a = false;
	while (a == false)
	{
		cout << "Enter password: ";
		getline(cin, userPassword);

		for (int x = 0; x < userPassword.length(); x++)//loop checks if there are spaces in password
		{
			if (userPassword[x] == ' ')
			{
				cout << "Password can't have any spaces. Please try again." << endl;
				break;
			}
			if (x == userPassword.length() - 1)
			{
				a = true;
			}
		}

	}
	cout << "Confirm Password: ";
	getline(cin, CP);
	while (CP != userPassword)
	{
		cout << "Passwords are not the same. Please try again " << endl;
		cout << "Confirm password: ";
		getline(cin, CP);
	}
}
//=========================================================================
void LoginUser::setFirstName()
{
	cout << "Enter your first name: ";
	cin >> firstName;
}
//===========================================================================
void LoginUser::setLastName()
{
	cout << "Enter your last name: ";
	cin >> lastName;
}
//=============================================================================
void LoginUser::setEmail()
{
	cout << "Enter your email: ";
	cin >> email;
}
//===========================================================================
string LoginUser::getUserName()
{
	return userName;
}
//==============================================
string LoginUser::getUserPassword()
{
	return userPassword;
}
//=======================================
string LoginUser::getFirstName()
{
	return firstName;
}
//==============================================
string LoginUser::getLastName()
{
	return lastName;
}
//================================================
string LoginUser::getEmail()
{
	return email;
}
//====================================================
string LoginUser::getPasswordHash()
{
	return passwordHash;
}
//========================================
void LoginUser::encryptPassword()
{
	
	string tempPassword = userPassword;
	char c;
	int cval;
	for (int x = 0; x < tempPassword.length(); x++)
	{
		c = tempPassword[x];
		cval = (int)c;
		cval = (126 - cval) / x + 33;
		c = (char)cval;
		passwordHash += c;
	}
}
//===========================================================================
/*bool LoginUser::authenticate()
{
	bool result;
	result = passwordHash == box.getPasswordHash(userName);
	return result;
}*/