#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

std::pair<std::string, std::string> &splitString(const std::string &str) {

  std::string left{str.substr(0, str.find('|'))};
  std::string right{str.substr(str.find('|') + 2)};
  static std::pair<std::string, std::string> splittedString{left, right};

  return splittedString;
}

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strinput;
  while (std::getline(inf, strinput)) {
    std::pair<std::string, std::string> splittedstring{splitString(strinput)};

    std::cout << splittedstring.first << '\n' << splittedstring.second;
  }
}
