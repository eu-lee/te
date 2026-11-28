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

    size_t targetRow = document.cursor.row;
    size_t targetCol = document.cursor.col;

    size_t curRow = 0;
    size_t curCol = 0;

    for(size_t pos = 0; pos < document.contents.size(); pos++){
        if(curRow == targetRow && curCol == targetCol){
            document.contents.insert(pos, textInput);

            //after insertion advance cursor once forward
            document.cursor.col++;
        }
        
        if(document.contents[pos] == '\n'){
            curRow++;
            curCol = 0;
        }
        else{
            curCol++;
        }


    }
    return;
}

void delete_at(Document & document){

    if (document.cursor.row == 0 && document.cursor.col == 0){
        return;
    }

    size_t targetRow = document.cursor.row;
    size_t targetCol = document.cursor.col;

    size_t curRow = 0;
    size_t curCol = 0;

    for(size_t pos = 0; pos < document.contents.size(); pos++){

        if(curRow == targetRow && curCol == targetCol){

            
            if (document.cursor.col > 0) {
                document.contents.erase(pos -1 , 1);
                document.cursor.col--;
            }
            else {
                document.cursor.row--;

                document.cursor.col = get_line_length(document, document.cursor.row);

                document.contents.erase(pos - 1, 1);
            }

            return;
        }

        if(document.contents[pos] == '\n'){
            curRow++;
            curCol = 0;
        }
        else{
            curCol++;
        }
        
    }
    return;

}


/*
dont know when the next time ill revisit this is, but work on fixing the delete logic. and wrap around. 

add enterkey pseudonym -> "\n" char inserted.

*/