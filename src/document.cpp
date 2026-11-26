#include "document.h"

#include <fstream>
#include <stdexcept>
#include <string>

Document load_file(const std::string& path){

    std::ifstream file(path);

    if (!file) {
        throw std::runtime_error("Could not open file: " + path);
    }

    Document document;

    std::string contents = "";

    std::string line = "";
    while(std::getline(file,line)){
        contents += line + "\n";
    }

    document.contents = contents;

    return document;
}


size_t get_line_length(const Document& document, size_t row){
    size_t curLineNum = 0;
    size_t curLineLength = 0;

    for(char c : document.contents){

        if(curLineNum == row){
            if(c == '\n'){
                return curLineLength;
            }

            curLineLength++;
            continue;
        }

        if(c == '\n'){
            curLineNum++;
        }

    }

    if(curLineNum == row){
        return curLineLength;
    }
    return 0;
}

size_t get_line_count(const Document & document){
    size_t numLines = 0;
    for( char c : document.contents){
        if(c == '\n'){
            numLines++;
        }
    }

    return numLines;
}

void insert_at(Document & document, const std::string& textInput){

    std::string updatedContents = document.contents;

    int targetRow = document.cursor.row;
    int targetCol = document.cursor.col;

    int curRow = 0;
    int curCol = 0;

    for(size_t pos = 0; pos < document.contents.size(); pos++){
        if(document.contents[pos] == '\n'){
            curRow++;
            curCol = 0;
        }
        else{
            curCol++;
        }

        if(curRow == targetRow && curCol == targetCol){
            document.contents.insert(pos+1, textInput);
        }
    }
    return;
}

