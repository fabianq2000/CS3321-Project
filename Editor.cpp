#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Editor.h"


// Runs the editor system
// Prints the menu and guides the user through the editor's various options

void Editor::initializeEditor(eBook& book) {
	int firstLineLoaded = 0;
	int input;
	int lastLineNum;
	int line;
	std::string text;
	std::string str;
	std::string formatting;


	// Extract the content from the eBook parameter
	std::vector<std::string> content = book.getContent();

	do {

		std::system("cls");

		//Display the eBook content NUM_LINES lines at a time, 
		//starting at firstLineLoaded which is initialized to 0
		displayContent(content, firstLineLoaded, NUM_LINES);
		std::cout << "------------------------------" << std::endl;

		// Display menu options
		displayOptions();

		//Select an option
		//1. Scroll up
		//2. Scroll down
		//3. Edit line
		//4. Delete line
		//5. Append line
		//6. Insert line
		//7. Format line
		//8. Save and quit
		//9. Quit without saving
		input = getUserInput(1,9);
		switch (input) {
		//1. Scroll up
		case 1:
			scrollUp(firstLineLoaded);
			break;
		//2. Scroll down
		case 2:
			lastLineNum = book.getContent().size();
			scrollDown(firstLineLoaded, lastLineNum);
			break;
		//3. Edit line
		case 3:
			line = getLineToEdit(content.size());
			if (line > 0) {
				str = content.at(line - 1);
				splitLine(str, formatting, text);
				editLine(text);
				str = formatting + "" + text;
				content.at(line - 1) = str;
			}
			break;
		//4. Delete line
		case 4:
			line = getLineToDelete(content.size());
			if (line > 0) {
				str = content.at(line - 1);
				std::cout << "Deleting line " << line << ": " << str << std::endl;
				std::cout << "------------------------------" << std::endl;
				std::cout << "1. Confirm" << std::endl;
				std::cout << "2. Cancel" << std::endl;
				input = getUserInput(1, 2);
				if (input == 1) {
					content.erase(content.begin()+input+1);
				}
			}
			break;
		//5. Append line
		case 5:
			content.push_back(getStringToAppend());
			break;
		//6. Insert line
		case 6:
			line = getLineToInsert(content.size());
			str = getStringToInsert();
			content.insert(content.begin() + line, str);
			break;
		//7. Format line
		case 7:
			line = getLineToFormat(content.size());
			str = content.at(line - 1);
			formatLine(str);
			content.at(line - 1) = str;
			break;
		//8. Save and quit
		case 8:
			book.updateContent(content);
			book.writeEbook();
			std::cout << "eBook saved to " << book.getFilename() << std::endl;
			system("pause");
		}
	} while (input != 8 && input !=9);

}

// Displays the content of the eBook starting at firstLine
// Displays numLines lines
void Editor::displayContent(std::vector<std::string> content, const int &firstLine, const int& numLines) {
	std::string format;
	std::string text;
	int lineNumber;
	for (int x = 0; x < numLines && x + firstLine < content.size(); x++) {
		splitLine(content.at(x + firstLine), format, text);
		getFormattingForPrinting(format);
		lineNumber = x + firstLine;
		std::cout << format << " | " << std::setw(3) << lineNumber + 1 << ": " << text << std::endl;
	}

	
}

// Splits a line of the content vector into the formatting section and actual test
// Example line in .txt : " is24 this text is part of the book "
void Editor::splitLine(const std::string& line, std::string& formatting, std::string& text) {
	size_t pos;
	std::string tmp = line;

	bool bold = false;
	bool italics = false;
	std::string fontsize;

	// Isolate the first section of the line containing formatting
	pos = tmp.find(DELIM);
	formatting = tmp.substr(0, pos);

	// Set tmp to the remaining portion of the string which contains the line contents
	tmp = tmp.substr(pos + 1);
	text = tmp;
}

// Prints the menu
void Editor::displayOptions() {
	std::cout << "Select an option: " << std::endl;
	std::cout << "1. Scroll up" << std::endl;
	std::cout << "2. Scroll down" << std::endl;
	std::cout << "3. Edit line" << std::endl;
	std::cout << "4. Delete line" << std::endl;
	std::cout << "5. Append line" << std::endl;
	std::cout << "6. Insert line" << std::endl;
	std::cout << "7. Format line" << std::endl;
	std::cout << "8. Save and quit" << std::endl;
	std::cout << "9. Quit without saving" << std::endl;

}

// Receives and validates integer input from the user
// Only accepts input between min and max, inclusive
// Any other input will prompt for the user to re-enter valid input
// min parameter must be >= 0
int Editor::getUserInput(const int& min, const int& max) {
	std::string s_input = "0";
	int input = -1;
	bool invalidInput;
	do {
		invalidInput = true;
		std::cout << ": ";

		// Receives an entire line from the user
		std::getline(std::cin, s_input);

		// Check if the input was actually numeric
		if (isNumeric(s_input)) {

			// If so, it is safe to convert to int type.
			input = stoi(s_input);
		}

		// If the input is outside of the acceptable range, set the invalidInput flag to true
		// If non-numeric input is received, input value remains -1 and triggers invalidInput flag
		invalidInput = input < min || input > max;
		
		if (invalidInput) {
			std::cout << "Please provide valid input number (" << min << "-"<< max <<")";
		}

	} while (invalidInput);
	return input;
}

// Cycles the display to show lines above the current cursor. 
// Does nothing if the display is already showing the first line
void Editor::scrollUp(int& firstLine) {
	firstLine -= NUM_LINES / 2;
	if (firstLine < 0) {
		firstLine = 0;
	}
}

// Cycles the display to show lines below the last line displayed
// Does nothing if the display is already showing the last line
void Editor::scrollDown(int& firstLine, const int& lastLine) {
	firstLine += NUM_LINES / 2;
	if (firstLine + NUM_LINES > lastLine) {
		firstLine = lastLine - NUM_LINES;
	}
	if (firstLine < 0) {
		firstLine = 0;
	}
}

// Receives a line number from the user
// only accepts input <= the number of lines in content
int Editor::getLineToEdit(const int& maxlines) {

	// If the content is empty
	if (maxlines == 0) {
		std::cout << "No lines to edit." << std::endl;
		system("pause");
		return 0;
	}
	std::cout << "Which line? ";

	return getUserInput(1, maxlines);
}

// Handles the menu and user input for editing a line in the eBook
// The line parameter is edited to contain the new line
void Editor::editLine(std::string & line) {
	int input = 0;
	std::string tmp;
	std::cout << "Editing: " << std::endl;
	std::cout << line << std::endl;
	std::cout << "------------------------------" << std::endl;
	getline(std::cin, tmp);
	std::cout << " << : " << line << std::endl;
	std::cout << " >> : " << tmp << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "1. Confirm" << std::endl;
	std::cout << "2. Cancel" << std::endl;
	input = getUserInput(1, 2);
	//1. Confirm
	if (input == 1) {
		line = tmp;
	}
	//2. Cancel
	// Do nothing just end the function


}

// Receives a line number from the user
// only accepts input <= the number of lines in content
int Editor::getLineToDelete(const int& maxlines) {
	// If the content is empty
	if (maxlines == 0) {
		std::cout << "No lines to delete." << std::endl;
		system("pause");
		return 0;
	}
	std::cout << "Which line? ";

	return getUserInput(1, maxlines);
}

// Receive string input from the user
std::string Editor::getStringToAppend() {
	std::string str;
	std::cout << "Input string to append: " << std::endl;
	getline(std::cin, str);
	return " " + str;
}

// Receives a line number from the user
// only accepts input <= the number of lines in content
int Editor::getLineToFormat(const int& maxlines) {
	// If the content is empty
	if (maxlines == 0) {
		std::cout << "No lines to format." << std::endl;
		system("pause");
		return 0;
	}
	std::cout << "Which line? ";

	return getUserInput(1, maxlines);
}

// Receives the line number where a new line of text should be added
// If 0, add before the first line
// If maxlines, add after the last line
int Editor::getLineToInsert(const int& maxlines) {
	std::cout << "After which line number should a new line be inserted? ";
	return getUserInput(0, maxlines);
}

// Receives a string from the user
std::string Editor::getStringToInsert() {
	std::string str;
	std::cout << "Input string to insert: " << std::endl;
	getline(std::cin, str);
	return " " + str;
}

// Handles the menu and user input for modifying formatting for a line
// Parameter: line: The raw line from the next file including formatting and text
// line is modified to reflect the formatting options the user selects
void Editor::formatLine(std::string& line) {
	std::string formatting;
	std::string text;
	// Split the line into strings containing formatting and text
	splitLine(line, formatting, text);

	// Initialize flags to false. If the flag(s) are found they will be updated to true
	bool bold = false;
	bool italic = false;

	// Initialize fontsize to a sentinal value that corresponds to no font size specified for the line
	int fontsize = -1;
	int input;

	// Variable to store the fontsize while it is a string type
	std::string s_fontsize;
	do {
		system("cls");
		std::cout << text << std::endl;
		std::cout << "------------------------------" << std::endl;
		std::cout << "Current formatting: " << std::endl;
		getFormatting(formatting, bold, italic, s_fontsize);

		// Check if the fontsize string is numeric
		if (isNumeric(s_fontsize)) {
			// If so, it is safe to convert to integer
			fontsize = stoi(s_fontsize);
		}

		// If the fontsize is not numeric for any reason, the -1 sentinal will ensure the fontsize is reset

		// Display the current formatting options in readable format
		// -------
		// Bold
		// Italicised
		// Font size: Not set
		// -------
		if (bold) {
			std::cout << "Bold" << std::endl;
		}
		if (italic) {
			std::cout << "Italicised" << std::endl;
		}
		std::cout << "Font size: ";
		if (fontsize > 0) {
			std::cout << fontsize;
		}
		else {
			std::cout << "Not set";
		}

		// Display formatting options
		std::cout << std::endl;
		std::cout << "------------------------------" << std::endl;
		std::cout << "1. Toggle bold" << std::endl;
		std::cout << "2. Toggle italics" << std::endl;
		std::cout << "3. Set font size" << std::endl;
		std::cout << "4. Return" << std::endl;

		input = getUserInput(1, 4);
		switch (input) {
		//1. Toggle bold
		case 1: 
			bold = !bold;
			break;
		//2. Toggle italics
		case 2:
			italic = !italic;
			break;
		case 3:
		//3. Set font size
			std::cout << "Font size (0 to unset): ";
			fontsize = getUserInput(0, 72);
			break;
		}
		// If there is a sensible font size set
		if (fontsize > 0)
			// Create a formatting string that includes font size
			formatting = generateFormattingStr(bold, italic, std::to_string(fontsize));
		else
			// Otherwise exclude the font size from the formatting string
			formatting = generateFormattingStr(bold, italic);
		// Recombine the new formatting string with the corresponding text from the book
		// If formatting doesn't change, line will not change either
		line = formatting + " " + text;

	} while (input != 4);


}

// Generates a precisely formatted string that can be stored in .txt 
// and used to retrieve formatting options
// excludes font size
std::string Editor::generateFormattingStr(bool bold, bool italic) {
	std::string result = "";
	if (bold) result.push_back('b');
	if (italic) result.push_back('i');
	return result;
}

// Generates a precisely formatted string that can be stored in .txt 
// and used to retrieve formatting options
// includes font size
std::string Editor::generateFormattingStr(bool bold, bool italic, std::string fontsize) {
	std::string result;
	result = generateFormattingStr(bold, italic);
	result = result + "s" + fontsize;
	return result;
}

// Parameter: formatting: The raw formatting string as stored in .txt
// Parameter: bold: Flag that will be updated if the letter 'b' is found in the formatting string
// Parameter: italic: Flag that will be updated if the letter 'i' is found in the formatting string
// Parameter: fontsize: String that will be populated if the letter 's' is found in the formatting string
// 's' will not be included in fontsize
// 's24' => fontsize = 24
// 's' is the flag that indicates a font size follows
void Editor::getFormatting(const std::string& formatting, bool& bold, bool& italic, std::string& fontsize) {
	bold = false;
	italic = false;

	size_t pos;
	std::string tmp;
	// Look for the letter 'b' in the formatting string
	if (formatting.find("b") != std::string::npos) {
		bold = true;
	}
	// Look for the letter 'i' in the formatting string
	if (formatting.find("i") != std::string::npos) {
		italic = true;
	}

	// Look for the letter 's' in the formatting string
	pos = formatting.find("s");
	if (pos != std::string::npos) {
		// Scan the rest of the formatting string and extract all digits in order
		for (int y = pos; y < formatting.length(); y++) {
			char c = formatting.at(y);
			if (c >= '0' && c <= '9') {
				// build a string containing the font size
				tmp.push_back(c);
			}
		}
		// store the font size back in the fontsize parameter
		fontsize = tmp;
	}
}

// Utility functin
// Checks if a string contains only numeric ( 0-9 ) character
bool Editor::isNumeric(std::string s) {
	int len = s.length();
	bool result = true;
	// If the string is empty
	if (len <= 0) {
		result = false;
	}
	for (int x = 0; x < len && result; x++) {
		if (!std::isdigit(s.at(x))) {
			result = false;
		}
	}
	return result;
}

// Takes a formatting string as a parameter then prints it with a constant length
// for the purpose of left aligning the content text
// This makes the text viewer look much neater and easier to read
void Editor::getFormattingForPrinting(std::string& f) {
	bool bold;
	bool italics;
	std::string fontsize;

	// Extract formatting values from the input string
	getFormatting(f, bold, italics, fontsize);

	// Clear the input string, preparing to build a specifically formatter version
	f.clear();

	// Either bold or blank space
	if (bold) {
		f.push_back('b');
	}
	else {
		f.push_back(' ');
	}
	// Either italics or blank space
	if (italics) {
		f.push_back('i');
	}
	else {
		f.push_back(' ');
	}
	// Prints the font size in a field of width 2
	for (int x = 2; x >= 0; x--) {
		if (x < fontsize.length()) {
			f.push_back(fontsize.at(fontsize.length() - x - 1));
		}
		else {
			f.push_back(' ');
		}
	}
}