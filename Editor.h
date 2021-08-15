#include<string>
#include<vector>
#include "eBook.h"

class Editor {
private:
	static const int NUM_LINES = 24;
	static const char DELIM = ' ';

	void displayContent(std::vector<std::string> content, const int& firstLine, const int& numLines);
	void displayOptions();
	void splitLine(const std::string& line, std::string& formatting, std::string& text);
	int getUserInput(const int& min, const int& max);
	void scrollUp(int& firstLine);
	void scrollDown(int& firstLine, const int& lastLine);
	int getLineToEdit(const int& maxlines);
	void editLine(std::string & line);
	int getLineToDelete(const int& maxlines);
	std::string getStringToAppend();
	int getLineToFormat(const int& maxlines);
	void formatLine(std::string& line);
	int getLineToInsert(const int& maxlines);
	std::string getStringToInsert();
	std::string generateFormattingStr(bool bold, bool italic);
	std::string generateFormattingStr(bool bold, bool italic, std::string fontsize);

	bool isNumeric(std::string s);
	void getFormatting(const std::string & formatting, bool &bold, bool &italic, std::string& fontsize);
	void getFormattingForPrinting(std::string& formatting);

public:
	void initializeEditor(eBook &book);


};