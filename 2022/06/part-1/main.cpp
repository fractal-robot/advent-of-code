#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "Unable to open file.";
    return 1;
  }

  std::string strInput;
  short counter{};

  while (std::getline(inf, strInput, '\n')) {
    for (std::size_t i{0}; i < std::size(strInput); ++i) {
      std::unordered_set<char> charSet;

      // Use a loop to insert characters into charSet
      for (std::size_t j{i}; j < i + 4; ++j) {
        charSet.insert(strInput[j]);
      }

      if (std::size(charSet) == 4) {
        std::cout << i + 4 << '\n';
        ++counter;
        break;
      }
    }
  }

  std::cout << '\n' << counter;
  return 0;
}
