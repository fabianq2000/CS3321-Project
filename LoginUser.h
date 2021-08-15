#pragma once

#ifndef LOGINUSER_H
#define LOGINUSER_H

#include <iostream>
#include <string>

#include "eBook.h"
using namespace std;

static const int MAX_EBOOKS_PER_USER = 48;

class LoginUser
{
private:
	string userName;
	string userPassword;
	string passwordHash;
	string firstName;
	string lastName;
	string email;
	std::vector<int> ebookIDs;
public:

	LoginUser();
	LoginUser(
		const std::string& username,
		const std::string& password,
		const std::string& first,
		const std::string& last,
		const std::string& email,
		vector<int> IDs
	);

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
	vector<int> getIDs();

	void printInfo();
	eBook createNewEbook();

	void addEbookByID(const int& ID);
	void printOwnedEbooks();

	void encryptPassword();//prototype
	//bool authenticate();//prototype
};
#endif // LOGINUSER_H