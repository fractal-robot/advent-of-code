#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

///
std::vector<int> &calculateValues(std::vector<int> &depths);
void calculateVariations(std::vector<int> &depths);
///

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

  calculateVariations(calculateValues(depths));
  return EXIT_SUCCESS;
}

std::vector<int> &calculateValues(std::vector<int> &depths) {

  static std::vector<int> values{};
  values.reserve(100);

  std::size_t i{1};
  for (int depth : depths) {
    values.emplace_back(depth + depths[i] + depths[i + 1]);

    ++i;

    if (i >= (std::size(depths) - 1)) {
      break;
    }
  }

  return values;
}

void calculateVariations(std::vector<int> &depths) {

  for (int i : depths) {
    std::cout << i << '\n';
  }

  std::cout << "\n\n\n\n";

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
    } else {
      std::cout << "no change" << '\n';
    }

    oldDepth = i;
  }

  std::cout << '\n' << totalIncreased;
}
