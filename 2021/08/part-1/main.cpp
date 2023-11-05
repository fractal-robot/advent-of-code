// 1: 2
// 4: 4
// 7: 3
// 8: 7

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

std::pair<std::string, std::string> splitString(const std::string &str) {

  std::string left{str.substr(0, str.find('|'))};
  std::string right{str.substr(str.find('|') + 1)};
  std::pair<std::string, std::string> splittedString{left, right};

  return splittedString;
}

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;
  int counter{};

  while (std::getline(inf, strInput)) {
    std::pair<std::string, std::string> splittedstring{splitString(strInput)};
    std::istringstream iss{splittedstring.second};
    std::string token;

    while (std::getline(iss, token, ' ')) {
      size_t strSize = std::size(token);
      if ((strSize >= 2 && strSize <= 4) || strSize == 7) {
        ++counter;
      }
    }
  }

  std::cout << counter;
  return EXIT_SUCCESS;
}
