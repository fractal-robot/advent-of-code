// using negative number to avoid creating boolean 2 dimentionnal arrays

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using boards = std::vector<std::vector<std::vector<int>>>;

// can't use std::string_view with constructor of std::istringstream
std::vector<int> &getValuesArray(const std::string &strInput) {
  static std::vector<int> values{};
  values.reserve(100);

  std::istringstream iss(strInput);
  std::string token;
  while (std::getline(iss, token, ',')) {
    int value = std::stoi(token);
    values.push_back(value);
  }

  return values;
}

void getBingoBoards(const std::string &strInput) { ; }

int main() {

  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;
  bool firstI{true};

  std::vector<int> *values;

  while (std::getline(inf, strInput)) {
    if (firstI) {
      values = &getValuesArray(strInput);
      firstI = false;

    } else {
      getBingoBoards(strInput);
    }
  }

  for (int i : *values) {
    std::cout << i << ' ';
  }

  return EXIT_SUCCESS;
}

// return by CONST reference
