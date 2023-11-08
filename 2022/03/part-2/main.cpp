
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

int main() {
  std::ifstream input{"input.txt"};
  if (!input) {
    std::cerr << "Unable to open file.";
  }

  std::string strInput;

  std::vector<std::string> valuesArray{};
  valuesArray.reserve(100);

  std::vector<char> commonCharacters{};
  commonCharacters.reserve(100);

  while (std::getline(input, strInput, '\n')) {
    valuesArray.emplace_back(strInput);
  }

  for (std::size_t i{0}; i < std::size(valuesArray); i += 3) {
    char commonCharacter;

    for (char c : valuesArray[i]) {
      for (char d : valuesArray[i + 1]) {
        for (char e : valuesArray[i + 2]) {
          if ((c == d) && (d == e)) {
            commonCharacter = e;
          }
        }
      }
    }
    commonCharacters.emplace_back(commonCharacter);
  }

  int sum{};
  for (char c : commonCharacters) {
    std::cout << c << ' ';

    if (c >= 97 && c <= 122) {
      sum += c - 96;
      std::cout << c - 96 << '\n';
    } else if (c >= 65 && c <= 90) {
      sum += c - 64 + 26;
      std::cout << c - 64 + 26 << '\n';

    } else {
      std::cerr << "Invalid character." << '\n';
      exit(1);
    }
  }

  std::cout << '\n' << sum;
}
