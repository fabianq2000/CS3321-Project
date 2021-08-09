#include <string>;
#include <vector>

class DocumentConverter {

	std::string loadInputContent(std::string filename);
	std::string generateOutputContent(std::vector<std::string> inputContent, std::string outputFileType);
	std::string generateOutputContent(std::vector<std::string> inputContent);
	void writeOutputContent(std::vector<std::string> outputContent, std::string outputFilename);


};