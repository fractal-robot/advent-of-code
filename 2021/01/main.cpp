#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> &getSortedData() {
  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  static std::vector<int> stackDepths{};
  stackDepths.reserve(100);

  std::string strInput;

  while (std::getline(inf, strInput)) {
    stackDepths.emplace_back(std::stoi(strInput));
  }

  return stackDepths;
}

int main() {

  std::vector<int> depths{getSortedData()};

  int oldDepth{};
  int totalIncreased{};

  for (int i : depths) {
    std::cout << i << ' ';

    if (oldDepth == 0) {
      std::cout << "N/A" << '\n';
    } else if (i > oldDepth) {
      std::cout << "increased" << '\n';
      ++totalIncreased;
    } else if (i < oldDepth) {
      std::cout << "decreased" << '\n';
    }

    oldDepth = i;

    std::cout << totalIncreased;
  }

  return EXIT_SUCCESS;
}
