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
  short counter{};
  while (std::getline(inf, strInput, '\n')) {
    for (std::size_t i{0}; i < std::size(strInput); ++i) {
      std::unordered_set<char> charSet = {strInput[i], strInput[i + 1],
                                          strInput[i + 2], strInput[i + 3]};
      if (std::size(charSet) == 4) {
        std::cout << i + 4 << '\n';
        ++counter;
        break;
      }
    }
  }

  std::cout << '\n' << counter;
}
