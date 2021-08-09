#include "Editor.h"
#include "DocumentConverter.h"
#include "Filehandler.h"

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
	// FileHandler testing

	void test_fileHandler() {
		int counter;
		std::vector<std::string> data;
		data.push_back("line 1");
		data.push_back("line 2");
		data.push_back("line 3");

		FileHandler fh;

		std::string filename;
		
		for (counter = 0; counter < 4; counter++) {
			filename = "testfile" + std::to_string(counter + 1) + ".txt";
			fh.saveToFile(filename, data);
		}

		for (counter = 0; counter < 4; counter++) {
			data.empty();
			filename = "testfile" + std::to_string(counter + 1) + ".txt";
			std::cout << filename << std::endl;
			data = fh.loadFile(filename);
			printVector(data);
			std::cout << std::endl;
		}

		for (counter = 0; counter < 2; counter++) {
			filename = "testfile" + std::to_string(counter + 1) + ".txt";
			std::string val = "appended";
			fh.appendFile(filename, val);
		}
		for (counter = 0; counter < 2; counter++) {
			data.empty();
			filename = "testfile" + std::to_string(counter + 1) + ".txt";
			std::cout << filename << std::endl;
			data = fh.loadFile(filename);
			printVector(data);
			std::cout << std::endl;
		}

	}
};