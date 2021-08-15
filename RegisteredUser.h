#pragma once

#ifndef REGISTEREDUSER_H
#define REGISTEREDUSER_H


#include "LoginUser.h"
#include <iostream>
#include <string>
using namespace std;

class RegisteredUser :public LoginUser
{
public:

	void addUser(string, string, string, string, string);//prototype
	//string getPasswordHash(string);//prototype
	//void updatePassword();//prototype
};
#endif // REGISTEREDUSER_H