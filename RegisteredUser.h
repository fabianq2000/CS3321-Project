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
	LoginUser* authenticate(const std::string& username, const std::string& password);

	string getPasswordHash(string);//prototype
	void updateUser(string, string, string, string, string, vector<int> IDs);
	//void updatePassword();//prototype
};
#endif // REGISTEREDUSER_H