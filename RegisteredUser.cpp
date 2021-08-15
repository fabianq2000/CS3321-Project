#include "RegisteredUser.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

static ofstream out;//object for output
static ifstream in;//object for input


static FileHandler fh;
static const std::string USERDB_FILENAME = "usersdb.txt";

void RegisteredUser::addUser(string a, string b, string c, string d, string e)
{
	out.open("usersdb.txt", ios::app);
	out << "Username: " << a << endl;
	out << "Password: " << b << endl;
	out << "First Name: " << c << endl;
	out << "Last Name: " << d << endl;
	out << "Email: " << e << endl;
	out << "eBook IDs: " << endl;
	out << "----------" << endl;
	out.close();
}

LoginUser* RegisteredUser::authenticate(const std::string &un, const std::string& pw){
	std::vector<std::string> users = fh.loadFile(USERDB_FILENAME); 

	bool match = false;
	std::string password;
	std::string fn;
	std::string ln;
	std::string email;
	std::string IDstring;
	std::string s = "0";
	std::string s2;
	int id;
	int total = 0;
	size_t pos;
	vector<int> IDs;
	for (int x = 0; x < users.size(); x++) {
		if (users.at(x).substr(0, 10) == "Username: ") {
			if (users.at(x).substr(10, un.length()) == un) {

				// extract password
				password = users.at(x + 1).substr(10);

				// check if the username and password match, proceed to generate a login user session
				if (password == getPasswordHash(pw)) {
					match = true;

					// If match, load in all of the user's other attributes
					fn = users.at(x + 2).substr(12);
					ln = users.at(x + 3).substr(11);
					email = users.at(x + 4).substr(7);
					IDstring = users.at(x + 5).substr(11);
					if (IDstring != "") {

						pos = IDstring.find(' ');
						s = IDstring.substr(0, pos);
						s2 = IDstring.substr(pos + 1);
						id = stoi(s);
						for (int x = 0; x < MAX_EBOOKS_PER_USER && id > 0; x++) {

							IDs.push_back(id);
							total++;
							id = 0;
							pos = s2.find(' ');
							if (pos != std::string::npos) {
								s = s2.substr(0, pos);
								s2 = s2.substr(pos + 1);
								if (s2.length() == 0) {
								}
								id = stoi(s);
							}
							else {
							}
						}
					}
					// Return a pointer to a new memory address storing the user's info
					return new LoginUser(un, pw, fn, ln, email, IDs);
				}
			}
		}
	}
	if (!match) {
		// If unable to authenticate, do not return any user's information
		return NULL;
	}
}

void RegisteredUser::updateUser(string un, string pw, string fn, string ln, string em, vector<int> IDs) {
	std::vector<std::string> users = fh.loadFile(USERDB_FILENAME);

	std::string IDstring = "";

	for (int x = 0; x < users.size(); x++) {
		if (users.at(x).substr(0, 10) == "Username: ") {
			if (users.at(x).substr(10, un.length()) == un) {
				users.at(x + 1) = "Password: " + pw;
				users.at(x + 2) = "First Name: " + fn;
				users.at(x + 3) = "Last Name: " + ln;
				users.at(x + 4) = "Email: " + em;
				for (int x = 0; x < IDs.size() && IDs.at(x); x++) {
					
					IDstring = IDstring + to_string(IDs.at(x)) + " ";
				}
				users.at(x + 5) = "eBook IDs: " + IDstring;

			}
		}
	}
	fh.saveToFile(USERDB_FILENAME, users);

}

//==============================================
string RegisteredUser::getPasswordHash(string a)
{
	return a;
}
//===========================================
//void RegisteredUser::updatePassword()
//{

//}