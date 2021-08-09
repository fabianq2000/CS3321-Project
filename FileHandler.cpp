#include<string>
#include<vector>
#include<fstream>

#include  "FileHandler.h""

std::vector<std::string> FileHandler::loadFile(std::string& filename) {
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

void FileHandler::saveToFile(std::string& filename, std::vector<std::string>& contents) {
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

void FileHandler::appendFile(std::string& filename, std::string& line) {
	std::vector<std::string> contents;
	contents = loadFile(filename);
	contents.push_back(line);
	saveToFile(filename, contents);
}