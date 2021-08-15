#include <iostream>
#include <fstream>
#include <string>
#include "LoginUser.h"
#include "RegisteredUser.h"
//#include "Editor.h"
//#include "eBook.h"
using namespace std;

int main()
{
	RegisteredUser info;
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
		info.setUserName();
		info.setUserPassword();
		info.setFirstName();
		info.setLastName();
		info.setEmail();
		//info.encryptPassword();
		info.addUser(info.getUserName(), info.getUserPassword(),info.getFirstName(),
					 info.getLastName(),info.getEmail());
	}
	else
	{
		//bool result = info.authenticate();
		//the menu below will display after the user enters the correct login information

		cout << "Welcome back " << endl;
		cout << "Choose one of the options below: " << endl;
		cout << "--------------------------------" << endl;
		cout << "1.See personal info" << endl;
		cout << "2.Update password" << endl;
		cout << "3.Update E-book description" << endl;
		cout << "4.Edit" << endl;
		cin >> choice;
		cout << endl;

		while (choice != '1' && choice != '2' && choice != '3' && choice != '4')
		{
			cout << "Option not available. Please try again" << endl << endl;
			cout << "Choose one of the choices below:" << endl;
			cout << "--------------------------------" << endl;
			cout << "1.See personal info" << endl;
			cout << "2.Update password" << endl;
			cout << "3.Update E-book description" << endl;
			cout << "4.Edit" << endl;
			cin >> choice;
			cout << endl;
		}
		switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			//info.updatePassword();
			break;
		case 4:
			break;
		}
	}
	
	
	


	system("pause");
	return 0;
}