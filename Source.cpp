#include <iostream>
#include <fstream>
#include <string>
#include "LoginUser.h"
#include "RegisteredUser.h"
#include "FileHandler.h"
#include "Editor.h"
#include "eBook.h"
using namespace std;

FileHandler fh;


void mainMenu();
void registerMenu();
void loginAttempt();
void loggedInMenu(LoginUser* loggedInUser);
void modifyMenu(LoginUser* loggedInUser);



int main()
{
	mainMenu();

	std::system("pause");
	return 0;
}

void mainMenu() {
	char choice;
	cout << "Choose one of the choices below:" << endl;
	cout << "--------------------------------" << endl;
	cout << "1.Register" << endl;
	cout << "2.Login" << endl;
	cin >> choice;

	while (choice != '1' && choice != '2')
	{
		cout << "Option not available. Please try again" << endl << endl;
		cout << "Choose one of the choices below:" << endl;
		cout << "--------------------------------" << endl;
		cout << "1.Register" << endl;
		cout << "2.Login" << endl;
		cin >> choice;
	}
	cin.ignore();

	if (choice == '1')//register
	{
		registerMenu();
	}
	else
	{
		loginAttempt();
	}
}

void registerMenu() {
	RegisteredUser info;
	info.setUserName();
	info.setUserPassword();
	info.setFirstName();
	info.setLastName();
	info.setEmail();

	info.addUser(info.getUserName(), info.getPasswordHash(info.getUserPassword()), info.getFirstName(),
		info.getLastName(), info.getEmail());
}

void loginAttempt() {
	RegisteredUser info;
	string username;
	string pass;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> pass;
	LoginUser* loggedInUser = info.authenticate(username, pass);
	if (loggedInUser != NULL) {
		loggedInMenu(loggedInUser);
	}
	else {
		cout << "Failed to log in. Please double check your username and password or register as a new user." << endl;
	}
}
void loggedInMenu(LoginUser* loggedInUser) {
	//the menu below will display after the user enters the correct login information
	char choice = ' ';
	Editor e;
	eBook myBook;
	cout << "Welcome back " << endl;
	while (choice != '4') {
		cout << "Choose one of the options below: " << endl;
		cout << "--------------------------------" << endl;
		cout << "1.See personal info" << endl;
		cout << "2.Create new eBook" << endl;
		cout << "3.Modify existing eBook" << endl;
		cout << "4.Exit" << endl;
		cin >> choice;
		cout << endl;


		while (choice < '1' || choice > '4')
		{
			cout << "Option not available. Please try again" << endl << endl;
			cout << "Choose one of the choices below:" << endl;
			cout << "--------------------------------" << endl;
			cout << "1.See personal info" << endl;
			cout << "2.Create new eBook" << endl;
			cout << "3.Load eBook" << endl;
			cout << "4.Exit" << endl;
			cin >> choice;
			cout << endl;


		}
		switch (choice)
		{
		case '1':
			loggedInUser->printInfo();
			break;
		case '2':
			cin.ignore();
			myBook = loggedInUser->createNewEbook();
			e.initializeEditor(myBook);
			break;
		case '3':
			modifyMenu(loggedInUser);
			break;
		}
	}
}

void modifyMenu(LoginUser* loggedInUser) {
	char choice = ' ';
	vector<int> IDs;
	int options[MAX_EBOOKS_PER_USER];
	IDs = loggedInUser->getIDs();
	if ( IDs.size() == 0) {
		cout << "No eBooks found. Please create a new eBook." << endl;;
	}
	else {
		cout << "Choose which eBook to edit: " << endl;
		for (int x = 0; x < IDs.size() && IDs.at(x) > 0; x++) {
			options[x] = IDs.at(x);
			cout << x + 1 << ". " << fh.getFileNameOfID(IDs.at(x)) << endl;
		}
		cin >> choice;
		cout << endl;
		while (choice < '1' || choice > '0' + IDs.size()
			) {
			cout << "Invalid choice. Please choose an option from the menu. " << endl;
			cout << "Choose which eBook to edit: " << endl;
			for (int x = 0; x < IDs.size() && IDs.at(x) > 0; x++) {
				options[x] = IDs.at(x);
				cout << x + 1 << ". " << fh.getFileNameOfID(IDs.at(x)) << endl;
			}
			cin >> choice;
			cout << endl;
		}
		eBook mybook(fh.getFileNameOfID(options[choice - '0' - 1]));
		Editor e;
		cin.ignore();
		e.initializeEditor(mybook);
	}

}