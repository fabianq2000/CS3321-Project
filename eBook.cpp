#include <iostream>
#include <string>
#include <vector>
#include "eBook.h"
#include "DocumentConverter.h"

const char DELIM = '|';
// Default constructor
//============================
eBook::eBook(const std::string & fn) {
	filename = fn;
	loadEbookFromFile(fn);
}

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
void eBook::setName(const std::string & n) {
	std::string oldname = getFilename();
	std::string newname = std::to_string(ID) + "_" + n;
	fh.renameFile(oldname, newname);
	name = n;
}
void eBook::loadEbookFromFile(const std::string & filename) {
	std::vector<std::string> data = fh.loadFile(filename);
	std::string metadata = data.at(0);
	size_t pos;
	description = data.at(1);
	content.clear();
	for (int x = 2; x < data.size(); x++) {
		content.push_back(data.at(x));
	}
	pos = metadata.find(DELIM);
	ID = stoi(metadata.substr(0, pos));
	metadata = metadata.substr(pos+1);
	pos = metadata.find(DELIM);
	name = metadata.substr(0, pos);
	owner = metadata.substr(pos+1);
	
}
void eBook::setFilename() {
	filename = std::to_string(ID) + "_" + name + ".txt";
}
void eBook::updateContent(const std::vector<std::string> & c) {
	content = c;
}
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
void eBook::deleteEbook() {
	fh.deleteFile(filename);
}
void eBook::setPublic() {
	isPublic = true;
}
void eBook::setPrivate() {
	isPublic = false;
}
void eBook::publish() {
	DocumentConverter dc;
	std::string fn = filename.substr(0, filename.length() - 4) + ".pdf";
	dc.writeOutputContent(content, fn);
}