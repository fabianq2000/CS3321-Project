#pragma once
#include <vector>

class FileHandler {
public:
	std::vector<std::string> loadFile(const std::string& filename);
	void saveToFile(const std::string& filename, const std::vector<std::string>& contents);
	void appendFile(const std::string& filename, const std::string& line);
	int deleteFile(const std::string& filename);
	int getLastIndex();
	int renameFile(const std::string& from, const std::string& to);
};