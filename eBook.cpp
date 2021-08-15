#include <iostream>
#include <string>
#include <vector>
#include "eBook.h"
#include "DocumentConverter.h"

// Delimiter for metadata in the .txt file that stores eBook contents
const char DELIM = '|';

// Filename constructor
// Loads all appropriate information from the file
eBook::eBook(const std::string & fn) {
	filename = fn;
	loadEbookFromFile(fn);
}

// Attribute constructor
// Allows an ebook object to be created directly from attributes passed to the constructor
eBook::eBook(const std::string & n, const std::string & o, const std::string & d, const bool & p) {
	name = n;
	owner = o;
	description = d;
	isPublic = p;
	setID();
	setFilename();
}

void eBook::updateDescription(const std::string & d) {
	description = d;
}

void eBook::setID() {
	ID = fh.getLastIndex() + 1;
}
void eBook::setOwner(const std::string & o) {
	owner = o;
}

// Changing the name involves renaming the file
// Filename format is ID_booktitle.txt
void eBook::setName(const std::string & n) {
	std::string oldname = getFilename();
	std::string newname = std::to_string(ID) + "_" + n;
	fh.renameFile(oldname, newname);
	name = n;
}

// Populates the attributes of the eBook from the meta data in the .txt file
// First 2 lines of the .txt file contain the metadata
// Format:
// ID|Title|Owner
// Description

void eBook::loadEbookFromFile(const std::string & fn) {

	// Load the contents of file fn into a vector of strings
	std::vector<std::string> data = fh.loadFile(fn);

	// The first line contains ID|Title|Owner metadata
	std::string metadata = data.at(0);

	size_t pos;

	// The second line contains the description
	description = data.at(1);

	// Make sure the content vector is empty and ready to load the text of the eBook
	content.clear();

	// Starting at the 3rd (index: 2) line of the vector, add every remaining line from the file input vector
	// Into the eBook content vector
	for (int x = 2; x < data.size(); x++) {
		content.push_back(data.at(x));
	}
	// Split up the metadata string into the individual attributes
	pos = metadata.find(DELIM);
	ID = stoi(metadata.substr(0, pos));
	metadata = metadata.substr(pos+1);
	pos = metadata.find(DELIM);
	name = metadata.substr(0, pos);
	owner = metadata.substr(pos+1);

	// Record the filename that was loaded
	filename = fn;
	
}

// Sets the filename using the appropriate ID_booktitle.txt format
void eBook::setFilename() {
	filename = std::to_string(ID) + "_" + name + ".txt";
}

void eBook::updateContent(const std::vector<std::string> & c) {
	content = c;
}

// Public methods which return class attributes

int eBook::getID() {
	return ID;
}

std::vector<std::string> eBook::getContent() {
	return content;
}

std::string eBook::getOwner() {
	return owner;
}

std::string eBook::getDescription() {
	return description;
}

std::string eBook::getFilename() {
	return filename;
}

// End attibute retrieval methods


// Writes the contents of the eBook to a text file
void eBook::writeEbook() {
	std::vector<std::string> data;
	std::string metadata = std::to_string(ID) + DELIM + name + DELIM + owner;
	data.push_back(metadata);
	data.push_back(description);
	for (int x = 0; x < getContent().size(); x++) {
		data.push_back(getContent().at(x));
	}
	std::cout << getFilename() << std::endl;
	fh.saveToFile(getFilename(), data);
}

// Deletes the eBook file from disk
// This is a DANGEROUS method there is no kind of confirmation
// Make sure to build in any necessary sanity checks to the functions that use this method
void eBook::deleteEbook() {
	fh.deleteFile(filename);
}

// Sets the eBook to public status
void eBook::setPublic() {
	isPublic = true;
}

// Sets the eBook to private status
void eBook::setPrivate() {
	isPublic = false;
}

// ************************************************************************
// *** DISABLE THIS METHOD IF YOU ARE DEBUGGING WITHOUT THE PDF LIBRARY ***
// ************************************************************************

// Converts the .txt eBook file into a .pdf document
void eBook::publish() {
	DocumentConverter dc;
	std::string fn = filename.substr(0, filename.length() - 4) + ".pdf";
	dc.writeOutputContent(content, fn);
}