#include <iostream>
#include <string>
#include <fstream>
#include "eBook.h"

using namespace std;

void updateDescription(std::string description)
{
	cout << "Please update the description." << endl;
	cin >> description;
}

string getContent(string name)
{
	string ebookName;
	ebookName = ebooks_database.getContentName(name);
	return ebookName;
}

string getOwner(string owner)//Returns Author
{
	return owner;
}

string getDescription(string description)//Returns description of eBook
{
	return description;
}

void setPublic(string name, bool isPublic)//If it is public, it stays that way, otherwise it sets it to public
{
	bool check;
	check = true;

	if (isPublic == check)
	{
		isPublic = true;
	}
	else
		isPublic = false;
}

void setPrivate(string name, bool isPublic)//If it is private, remain, otherwise set private;
{
	bool check;
	check = false;

	if (isPublic == check)
	{
		isPublic = false;
	}
	else
		isPublic = true;
}

int main()
{
	eBook book;
}


