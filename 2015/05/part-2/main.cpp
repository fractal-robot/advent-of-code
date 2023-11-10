#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

using namespace std::string_literals;

// I should have been using str_view for the previous part
bool checkForPairs(std::string_view strInput) {

  for (std::size_t i{0}; i < size(strInput); ++i) {
    std::string testedString{strInput[i], strInput[i + 1]};

    for (std::size_t j{i + 2}; j < size(strInput); ++j) {
      std::string comparedString{strInput[j], strInput[j + 1]};

      if (testedString == comparedString) {
        return true;
      }
    }
  }

  return false;
}

bool checkRepetition(std::string_view strInput) {

  for (std::size_t i{0}; i < size(strInput); ++i) {
    if (strInput[i] == strInput[i + 2]) {
      return true;
    }
  }

  return false;
}

int main() {
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::string strInput;
  int counter{};

  while (std::getline(inf, strInput, '\n')) {

    if (checkForPairs(strInput) && checkRepetition(strInput)) {
      ++counter;
    }
  }

  std::cout << counter;
  return EXIT_SUCCESS;
}
