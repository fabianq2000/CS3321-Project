#pragma once

#ifndef LOGINUSER_H
#define LOGINUSER_H

#include <iostream>
#include <string>
using namespace std;

class LoginUser
{
private:
	string userName;
	string userPassword;
	string passwordHash;
	string firstName;
	string lastName;
	string email;
public:
	void setUserName();//prototype
	void setUserPassword();//prototype
	void setFirstName();//prototype
	void setLastName();//prototype
	void setEmail();//prototype

	string getUserName();//prototype
	string getUserPassword();//prototype
	string getFirstName();//prototype
	string getLastName();//prototype
	string getEmail();//prototype
	string getPasswordHash();//prototype

	void encryptPassword();//prototype
	//bool authenticate();//prototype
};
#endif // LOGINUSER_H