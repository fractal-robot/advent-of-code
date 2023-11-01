#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Coordinates = std::array<int, 4>;

class Data {

public:
  void extractValues(std::string &strInput) {
    std::size_t separator = strInput.find(" -> ");
    strInput.replace(separator, 4, ",");

    std::istringstream iss(strInput);
    std::string token;

    std::size_t i{0};
    while (std::getline(iss, token, ',')) {
      coordinates[i] = std::stoi(token);
      ++i;
    }

    for (int c : coordinates) {
      std::cout << c << ' ';
    }
    if (checkOneLine(coordinates)) {
      std::cout << "is a line \n";
    } else {
      std::cout << "is not a line \n";
    }
  }

private:
  bool checkOneLine(Coordinates &coordinates) {

    if (coordinates[0] == coordinates[2] || coordinates[1] == coordinates[3]) {
      return true;
    }

    return false;
  }

private:
  Coordinates coordinates;
};

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  Data data;

  std::string strInput;
  while (std::getline(inf, strInput)) {
    data.extractValues(strInput);
  }
}
