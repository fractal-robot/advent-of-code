#include <array>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

constexpr int lineLength{100};

void getValues(std::vector<std::vector<short>> &valuesArray) {

  int sumValues{};

  for (std::size_t i{}; i < std::size(valuesArray); ++i) {
    for (std::size_t j{}; j < lineLength; ++j) {

      int counter{0};

      if (i < std::size(valuesArray) && j + 1 < lineLength) {
        if (valuesArray[i][j] < valuesArray[i][j + 1]) {
          ++counter;
        }
      } else {
        ++counter;
      }
      if (i < std::size(valuesArray) && j - 1 < lineLength) {
        if (valuesArray[i][j] < valuesArray[i][j - 1]) {
          ++counter;
        }
      } else {
        ++counter;
      }
      if (i - 1 < std::size(valuesArray) && j < lineLength) {
        if (valuesArray[i][j] < valuesArray[i - 1][j]) {
          ++counter;
        }
      } else {
        ++counter;
      }

      if (i + 1 < std::size(valuesArray) && j < lineLength) {
        if (valuesArray[i][j] < valuesArray[i + 1][j]) {
          ++counter;
        }
      } else {
        ++counter;
      }

      if (counter == 4) {
        sumValues += valuesArray[i][j] + 1;
      }
    }
  }
}

int main() {

  std::ifstream input{"input.txt"};

  std::string strInput;
  std::vector<std::vector<short>> valuesArray;

  while (std::getline(input, strInput)) {
    std::cout << strInput << '\n';

    std::vector<short> line{};
    line.reserve(lineLength);

    for (char value : strInput) {
      line.emplace_back(value - 48);
    }

    valuesArray.emplace_back(line);
  }

  getValues(valuesArray);
}
