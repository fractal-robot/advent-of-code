#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
int main() {
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::string strInput;
  std::getline(inf, strInput, '\n');

  int counter{};
  for (char c : strInput) {
    if (c == '(') {
      ++counter;
    } else if (c == ')') {
      --counter;
    }
  }

  std::cout << counter;
}
