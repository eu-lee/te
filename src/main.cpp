#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/screen/color.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;
using std::ifstream;


struct Document{
  std::string contents;
};


Document load_file(const string& path){

  ifstream file(path);

  if (!file) {
    throw std::runtime_error("Could not open file: " + path);
  }

  Document document;

  string contents = "";
  
  string line = "";
  while(std::getline(file,line)){
    contents += line + "\n";
  }

  document.contents = contents;

  return document;
}


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
  
  Document fileContents = load_file(fileLocation);

  auto editor = Renderer([&] {

    return vbox({
      text("Eugene's Text Editor")
          | bold
          | center
          | color(Color::Blue),

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

    return false;
  });

  screen.Loop(editor);

  return 0;
}