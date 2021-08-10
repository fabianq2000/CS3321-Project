#include <string>
#include <vector>

#include "hpdf.h"
#define HPDF_DLL

class DocumentConverter {
private:
	void printLine(const std::string& line, const HPDF_Font& font, const int& size, const HPDF_Page& page, const HPDF_REAL& width, const HPDF_REAL& height);
public:
	std::string loadInputContent(std::string filename);
	std::string generateOutputContent(std::vector<std::string> inputContent, std::string outputFileType);
	std::string generateOutputContent(std::vector<std::string> inputContent);
	void writeOutputContent(std::vector<std::string> outputContent, std::string outputFilename);
};