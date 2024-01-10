#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main() {
  std::ifstream file{"input.txt"};
  if (!file.is_open()) {
    std::cerr << "Unable to open input file.";
  }
  std::string strInput;
  int total{};
  while (std::getline(file, strInput, '\n')) {
    std::cout << strInput << '\n';
    std::string digits{};

    for (char c : strInput) {
      if (std::isdigit(c)) {
        digits += c;
        break;
      }
    }

    for (auto c = strInput.rbegin(); c != strInput.rend(); ++c) {
      if (std::isdigit(*c)) {
        digits += *c;
        break;
      }
    }
    std::cout << digits << '\n';

    if (!digits.empty())
      total += std::stoi(digits);

    std::cout << total << '\n';
  }

  std::cout << total;

  return EXIT_SUCCESS;
}
