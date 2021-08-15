#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <filesystem>
#include <iostream>

#include  "FileHandler.h"

namespace fs = std::filesystem;

// Load contents from File

/// <summary>
/// Loads the specified text file into a vector of strings corresponding to each line on text in the file
/// </summary>
/// <param name="filename">Name of file to load</param>
/// <returns>Vector of string corresponding to lines of text in the file</returns>
std::vector<std::string> FileHandler::loadFile(const std::string& filename) {
	std::ifstream inFile;
	std::vector<std::string> contents;
	std::string line;
	inFile.open(filename);
	if (inFile) {
		while (std::getline(inFile, line)) {
			contents.push_back(line);
		}
	}
	inFile.close();
	return contents;
}

// Save contents to File

/// <summary>
/// Saves the specified vector of strings in a file called filename
/// </summary>
/// <param name="filename">Name of the file to save as</param>
/// <param name="contents">Vector of strings corresponding to lines of text to save in the file</param>
void FileHandler::saveToFile(const std::string& filename, const std::vector<std::string>& contents) {
	std::ofstream outFile;
	std::string line;
	outFile.open(filename);
	if (outFile) {
		for (int counter = 0; counter < contents.size(); counter++) {
			line = contents.at(counter);
			outFile << line << std::endl;
		}
	}
	outFile.close();
}

// Append Line of Text to File

/// <summary>
/// Adds one line of text to the end of the file called filename
/// </summary>
/// <param name="filename">Name of the file to append to</param>
/// <param name="line">The line to append to the end of the file</param>
void FileHandler::appendFile(const std::string& filename, const std::string& line) {
	std::vector<std::string> contents;
	contents = loadFile(filename);
	contents.push_back(line);
	saveToFile(filename, contents);
}

// Delete file

/// <summary>
/// Deletes the file called filename
/// </summary>
/// <param name="filename">Name of the file to delete</param>
/// <returns>0 if successful, nonzero if failure corresponding to error code of cstdio remove function</returns>
int FileHandler::deleteFile(const std::string& filename) {
	char file[256];
	strcpy_s(file, filename.c_str());
	return remove(file);
}


int FileHandler::getLastIndex() {
	int lastIndex = 0;
	int index = lastIndex;
	std::string fn;
	std::string path = ".";
	std::string strindex;
	bool isNumeric = true; 
	for (const auto& entry : fs::directory_iterator(path)) {
		fn = entry.path().string();
		if (fn.substr(fn.length() - 4) == ".txt") {
			strindex = fn.substr(0, fn.find('_'));
			strindex = strindex.substr(2);

			// test if the filename substring is fully numeric
			isNumeric = true;
			for (int x = 0; x < strindex.length() && isNumeric; x++) {
				if (isdigit(strindex.at(x)) == 0) {
					isNumeric = false;
				}
			}
			if (isNumeric) {
				index = stoi(strindex);
				if (index > lastIndex) {
					lastIndex = index;
				}
			}
		}
	}
	return lastIndex;
}

std::string FileHandler::getFileNameOfID(const int& ID) {
	std::string fn;
	std::string strindex;
	std::string path = ".";
	int index;
	bool isNumeric = true;
	for (const auto& entry : fs::directory_iterator(path)) {
		fn = entry.path().string();
		if (fn.substr(fn.length() - 4) == ".txt") {
			strindex = fn.substr(0, fn.find('_'));
			strindex = strindex.substr(2);

			// test if the filename substring is fully numeric
			isNumeric = true;
			for (int x = 0; x < strindex.length() && isNumeric; x++) {
				if (isdigit(strindex.at(x)) == 0) {
					isNumeric = false;
				}
			}
			if (isNumeric) {
				index = stoi(strindex);
				if (index == ID) {
					return fn;
				}
			}
		}
	}
	return "";
}


int FileHandler::renameFile(const std::string& from, const std::string& to) {
	char oldname[256];
	char newname[256];
	strcpy_s(oldname, from.c_str());
	strcpy_s(newname, to.c_str());
	return rename(oldname, newname);
}