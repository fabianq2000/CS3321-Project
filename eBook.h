//eBook Class file for Software engineering
//Nereo Hoill
//

#ifndef EBOOK_H
#define EBOOK_H


class eBook 
{
private:
	int ID;
	std::string name;
	std::string owner; //Author
	std::string content;
	std::string fileType; // .pdf or .txt
	std::string description;
	bool isPublic; //Wether or not it is publically accessible
public:
	void updateDescription(std::string description);
	std::string getContent(std::string name);
	std::string getOwner(std::string owner);
	std::string getDescription(std::string description);
	void writeEbook(std::string name, std::string content);
	void setPublic(std::string name, bool isPublic);
	void setPrivate(std::string name, bool isPublic);

	eBook() //default constructor
	{

	}

	eBook(string n, string o, string c, string fT, string d, bool P) // constructor with parameters
	{
		name = n;
		owner = o;
		content = c;
		fileType = fT;
		description = d;
		isPublic = P;
	}

	
	


};




#endif







