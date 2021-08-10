
class FileHandler {
public:
	std::vector<std::string> loadFile(const std::string& filename);
	void saveToFile(std::string& filename, std::vector<std::string>& contents);
	void appendFile(std::string& filename, std::string& line);
};