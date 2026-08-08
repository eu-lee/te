#include "document.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <iostream>

using std::string;
using std::ifstream;


ftxui::Elements render_document(const Document& document){

  ftxui::Elements output;

  std::stringstream stream(document.contents);

  string line;

  while(std::getline(stream, line)){
    output.push_back(ftxui::text(line));
  }

  return output;
}


// main render
int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr << "Missing file location. Usage: te <path to file>\n";
    return 1;
  }

  using namespace ftxui;

  string fileLocation = argv[1];
  
  Document fileContents;

  try{
    fileContents = load_file(fileLocation);
  }
  catch(const std::runtime_error &e){
    std::cerr << e.what() <<"\n";
    return 1;
  }

  

  auto editor = Renderer([&] {

    return vbox({
      text("Eugene's Text Editor")
          | bold
          | center
          | color(Color::Blue),

      separator(),

      vbox({
          text("Current cursor location"),
          text("row: " + std::to_string(fileContents.cursor.row)),
          text("col: " + std::to_string(fileContents.cursor.col)),
        }),

      separator(),

      vbox(std::move(render_document(fileContents)))
          | border
          | flex,

        
    });


  });

  auto screen = ScreenInteractive::Fullscreen();

// event handling

  editor |= CatchEvent([&](Event event) {
    if (event == Event::CtrlC) {
      screen.Exit();
      return true;
    }

    if (event == Event::ArrowLeft) {
      if(fileContents.cursor.col >0){
        fileContents.cursor.col--;
      }

      return true;
    }

    if (event == Event::ArrowRight){

      size_t lineLength = get_line_length(fileContents, fileContents.cursor.row);

      if(fileContents.cursor.col < lineLength){
        fileContents.cursor.col++;
      }

      return true;
    }

    if (event == Event::ArrowUp){

      if(fileContents.cursor.row >0){
        fileContents.cursor.row--;
      }

      fileContents.cursor.col = std::min(fileContents.cursor.col,
        get_line_length(fileContents, fileContents.cursor.row));

      return true;
    }

    if (event == Event::ArrowDown){
      
      size_t numLines = get_line_count(fileContents);

      if(fileContents.cursor.row + 1< numLines){
        fileContents.cursor.row++;
      }

      fileContents.cursor.col = std::min(fileContents.cursor.col,
        get_line_length(fileContents, fileContents.cursor.row));


      return true;
    }

    return false;
  });

  screen.Loop(editor);

  return 0;
}