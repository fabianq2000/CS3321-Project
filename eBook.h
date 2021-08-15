//eBook Class file for Software engineering
//Nereo Hoill
//

#include <string>
#include <vector>
#include "FileHandler.h"

#ifndef EBOOK_H
#define EBOOK_H


class eBook
{
private:
	int ID;
	std::string name;
	std::string owner; //Author
	std::vector<std::string> content;
	std::string description;
	std::string filename;
	bool isPublic; //Wether or not it is publically accessible
	FileHandler fh;

public:
	void updateDescription(const std::string & description);
	void setID();
	void setOwner(const std::string & owner);
	void setName(const std::string & name);
	void loadEbookFromFile(const std::string& filename);
	void setFilename();
	void updateContent(const std::vector<std::string>& content);
	int getID();
	std::vector<std::string> getContent();
	std::string getOwner();
	std::string getDescription();
	std::string getFilename();
	void writeEbook();
	void deleteEbook();
	void setPublic();
	void setPrivate();

	void publish();

	// Default constructor
	//============================
	eBook();


	eBook(const std::string & filename); 

	// Constructor with parameters
	//============================
	eBook(const std::string& n, const std::string& o, const std::string& d, const bool& P);








};

#endif