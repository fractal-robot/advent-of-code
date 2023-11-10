#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

using namespace std::string_literals;

bool checkForVowels(const std::string &strInput) {
  std::array vowels{'a', 'e', 'i', 'o', 'u'};

  int counter{};
  for (char c : strInput) {
    for (char d : vowels) {
      if (c == d) {
        ++counter;
      }
    }
  }

  return counter >= 3 ? true : false;
}

bool checkDoubleLetters(const std::string &strInput) {
  char oldLetter{};

  for (char c : strInput) {
    if (c == oldLetter) {
      return true;
    }

    oldLetter = c;
  }

  return false;
}

bool shouldNotContain(const std::string &strInput) {
  std::array notContain{"ab"s, "cd"s, "pq"s, "xy"s};

  for (std::size_t i{0}; i < size(strInput) - 1; ++i) {
    for (std::string s : notContain) {
      if (strInput[i] == s[0] && strInput[i + 1] == s[1]) {
        return false;
      }
    }
  }

  return true;
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

    if (checkForVowels(strInput) && checkDoubleLetters(strInput) &&
        shouldNotContain(strInput)) {
      ++counter;
    }
  }

  std::cout << counter;
  return EXIT_SUCCESS;
}
