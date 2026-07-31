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


string load_file(const string& path){
  string contents = "";

  ifstream file(path);

  string line = "";
  while(std::getline(file,line)){
    contents += line + "\n";
  }

  return contents;
}

// main render
int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr << "Missing file location. Usage: te <path to file>\n";
    return 1;
  }

  using namespace ftxui;

  string fileLocation = argv[1];
  string fileContents = load_file(fileLocation);

  auto editor = Renderer([&] {
    Elements lines;

    std::stringstream stream(fileContents);
    string line;

    while (std::getline(stream, line)) {
      lines.push_back(text(line));
    }

    return vbox({
      text("Eugene's Text Editor")
          | bold
          | center
          | color(Color::Blue),

      separator(),

      vbox(std::move(lines))
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