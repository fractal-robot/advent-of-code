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
#include <string_view>
#include <utility>
#include <vector>

std::pair<std::string, std::string> splitString(const std::string &str) {

  std::string left{str.substr(0, str.find('|'))};
  std::string right{str.substr(str.find('|') + 1)};
  std::pair<std::string, std::string> splittedString{left, right};

  return splittedString;
}

std::string &getElement(std::string &values, std::size_t desiredLength) {

  std::istringstream iss{values};
  static std::string token;

  while (std::getline(iss, token, ' ')) {
    if (std::size(token) == desiredLength) {
      return token;
    }
  }
  return token;
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

    std::string one{getElement(splittedstring.first, 2)};
    std::string four{getElement(splittedstring.first, 4)};
    std::string seven{getElement(splittedstring.first, 3)};
    std::string eight{getElement(splittedstring.first, 7)};

    std::cout << one << ' ' << four << ' ' << seven << ' ' << eight;

    std::istringstream issFirst{splittedstring.first};
    std::istringstream issSecond{splittedstring.second};
    std::string token;

    while (std::getline(issSecond, token, ' ')) {
      size_t strSize = std::size(token);
      if ((strSize >= 2 && strSize <= 4) || strSize == 7) {
        ++counter;
      }
    }
  }

  std::cout << counter;
  return EXIT_SUCCESS;
}
