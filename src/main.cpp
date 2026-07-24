#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>
#include <fstream>

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


int main(int argc, char* argv[]) {

  string fileLocation = argv[1];

  string fileContents = load_file(fileLocation);


  using namespace ftxui;
 
  // Define the document structure
  Element document = vbox({
    text("Eugene's Text Editor") | bold | center,
    separator(),
      vbox({
        text(fileContents) | flex,
      }) | border | flex,
  });
 
  // Create the screen and render
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  screen.Print();
 
  return 0;
}
