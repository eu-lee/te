#include "document.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
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