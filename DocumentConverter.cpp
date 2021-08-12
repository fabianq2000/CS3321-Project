#include <string>
#include <setjmp.h>
#include <iostream>

#include "hpdf.h"
#include "DocumentConverter.h"

jmp_buf env;

#define HPDF_DLL

void error_handler(HPDF_STATUS   error_no,
    HPDF_STATUS   detail_no,
    void* user_data)
{
    printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
        (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

const int INIT_FONT_INDEX = 8; // initialize to Times-Roman


const char* font_list[] = {
    "Courier",
    "Courier-Bold",
    "Courier-Oblique",
    "Courier-BoldOblique",
    "Helvetica",
    "Helvetica-Bold",
    "Helvetica-Oblique",
    "Helvetica-BoldOblique",
    "Times-Roman",
    "Times-Bold",
    "Times-Italic",
    "Times-BoldItalic",
    "Symbol",
    "ZapfDingbats",
    NULL
};

void DocumentConverter::writeOutputContent(std::vector<std::string> outputContent, std::string outputFilename) {
   
    const char* page_title = "words";
    HPDF_Doc  pdf;
    char fname[256];
    HPDF_Page page, page2;
    HPDF_Font def_font;
    HPDF_REAL tw;
    HPDF_REAL height;
    HPDF_REAL width;

    int mariginw = 50;
    int mariginh = 50;

    //flags

    bool bold;
    bool italics;

    int font_index = INIT_FONT_INDEX; // initialize to arial
    int font_size = 12;

    std::string line;
    std::string formatting, line_num, text;

    size_t pos = 0;

    strcpy_s(fname, outputFilename.c_str());

    pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
        printf("error: cannot create PdfDoc object\n");
        return;
    }

    if (setjmp(env)) {
        HPDF_Free(pdf);
        return;
    }

    /* Add a new page object. */
    page = HPDF_AddPage(pdf);

    height = HPDF_Page_GetHeight(page);
    width = HPDF_Page_GetWidth(page);

    width =     mariginw;
    height = height - mariginh;

    for (int x = 0; x < outputContent.size(); x++) {
        bold = false;
        italics = false;
        font_index = INIT_FONT_INDEX;

        line = outputContent.at(x);
        pos = line.find(" ");
        formatting = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(" ");
        line_num = line.substr(0, pos);
        text = line.substr(pos + 1);
        if (formatting.find("b") != std::string::npos) {
            bold = true;
        }
        if (formatting.find("i") != std::string::npos) {
            italics = true;
        }
        pos = formatting.find("s");
        if (pos != std::string::npos) {
            line.clear();
            for (int y = pos; y < formatting.length(); y++) {
                char c = formatting.at(y);
                if (c >= 48 && c <= 57) {
                    line.push_back(c);
                }
            }
            font_size = stoi(line);
        }
        font_index += bold + 2 * italics;
        def_font = HPDF_GetFont(pdf, font_list[font_index], NULL);

        height = height - font_size - 2;
        printLine(text, def_font, font_size, page, width, height);
        
    }


    HPDF_SaveToFile(pdf, fname);

    /* clean up */
    HPDF_Free(pdf);

    return;

}
void DocumentConverter::printLine(const std::string &line, const HPDF_Font &font, const int& size, const HPDF_Page &page, const HPDF_REAL &width, const HPDF_REAL& height) {
    char cline[256];
    strcpy_s(cline, line.c_str());
    HPDF_Page_SetFontAndSize(page, font, size);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, width, height, cline);
    HPDF_Page_EndText(page);
    //HPDF_Page_MoveTextPos(page, 60, height - 55);
}
