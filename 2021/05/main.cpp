#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::array<int, 4> &extractValues(std::string &strInput) {
  std::size_t separator = strInput.find(" -> ");
  strInput.replace(separator, 4, ",");

  static std::array<int, 4> coordinates;

  std::istringstream iss(strInput);
  std::string token;

  int i{0};
  while (std::getline(iss, token, ',')) {
    coordinates[i] = std::stoi(token);
    ++i;
  }

  return coordinates;
}

int main() {

  std::array<int, 4> coordinates;

  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;
  while (std::getline(inf, strInput)) {
    coordinates = extractValues(strInput);

    for (int i : coordinates) {
      std::cout << i << ' ';
    }

    std::cout << '\n';
  }
}
