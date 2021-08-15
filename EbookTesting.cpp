#include "Editor.h"
#include "DocumentConverter.h"
#include "eBook.h"

#include <string>
#include <vector>
#include <iostream>

class EbookTesting {
private:
	void printVector(std::vector<std::string>& vec) {
		for (int x = 0; x < vec.size(); x++) {
			std::cout << vec.at(x) << std::endl;
		}
	}
public:

	void testEbook() {
		std::string name = "Test ebook name";
		std::string owner = "Test ebook owner";
		std::string description = "This is a test ebook";
		std::vector<std::string> content;
		content.push_back("bs24 1 This is line 1 of the test ebook");
		content.push_back("s18 2 This is line 2 of the test ebook");
		content.push_back("s18 3 This is line 3 of the test ebook");
		content.push_back(" 4 ");
		content.push_back("s18 5 There should be an empty line above this one");
		content.push_back("bs24 6 Bold font and larger");
		content.push_back("is12 7 Italic font and larger");
		content.push_back("bis48 8 Very large bold italic");

		eBook myBook(name, owner, description, false);
		myBook.updateContent(content);
		
		std::cout << "Filename: " << myBook.getFilename() << std::endl;
		std::cout << "Owner: " << myBook.getOwner() << std::endl;
		std::cout << "Description: " << myBook.getDescription() << std::endl;
		
		std::vector<std::string> myContent = myBook.getContent();
		std::cout << "Content: " << std::endl;
		for (int x = 0; x < myContent.size(); x++) {
			std::cout << myContent.at(x) << std::endl;
		}
		std::cout << std::endl;

		std::cout << "attempting to write to " << myBook.getFilename() << std::endl;
		myBook.writeEbook();
		myBook.publish();

		eBook myBook2(myBook.getFilename());
		std::cout << "Filename: " << myBook2.getFilename() << std::endl;
		std::cout << "Owner: " << myBook2.getOwner() << std::endl;
		std::cout << "Description: " << myBook2.getDescription() << std::endl;

		myContent = myBook2.getContent();
		std::cout << "Content: " << std::endl;
		for (int x = 0; x < myContent.size(); x++) {
			std::cout << myContent.at(x) << std::endl;
		}
		std::cout << std::endl;

	}

	void testEditor() {
		eBook testBook("1_Test ebook name.txt");
		Editor e;
		e.initializeEditor(testBook);
	}
};