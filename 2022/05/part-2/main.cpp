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
  }

  std::string strInput;

  while (std::getline(inf, strInput, '\n')) {
    for (std::size_t i{0}; i < std::size(strInput); ++i) {
      std::unordered_set<char> charSet;

      for (std::size_t j{i}; j < i + 14; ++j) {
        charSet.insert(strInput[j]);
      }

      if (std::size(charSet) == 14) {
        std::cout << i + 14 << '\n';
        break;
      }
    }
  }

  return 0;
}
