
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

  std::vector<char> commonCharacters{};
  commonCharacters.reserve(100);

  while (std::getline(input, strInput, '\n')) {
    assert(std::size(strInput) % 2 == 0);
    std::size_t divisor{std::size(strInput) / 2};

    std::string firstCompartment{strInput.substr(0, divisor)};
    std::string secondCompartment{strInput.substr(divisor)};

    char commonCharacter;
    for (char c : firstCompartment) {
      for (char d : secondCompartment) {
        if (c == d) {
          commonCharacter = d;
        }
      }
    }

    commonCharacters.emplace_back(commonCharacter);
  }

  long sum{};
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
