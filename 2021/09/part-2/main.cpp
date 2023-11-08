// I should have been using a struct to mark the numbers!

#include <array>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr int lineLength{10};
// so we assume that the implementation of short is two bytes
constexpr short shortMinCapacity{-32768};

struct Bassin {
  std::pair<int, int> lavaTubeCoordinates{};
  std::vector<std::pair<int, int>> adjacentTube{};
};

std::vector<std::vector<short>>
setValues(std::vector<std::vector<short>> &valuesArray) {

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

        if (valuesArray[i][j] == 0) {
          // so we assume that the implementation of short is two bytes
          valuesArray[i][j] = shortMinCapacity;
        } else {
          valuesArray[i][j] = -valuesArray[i][j];
        }
      }

      std::cout << valuesArray[i][j] << ' ';
    }

    std::cout << '\n' << sumValues;
  }

  return valuesArray;
}

std::vector<std::vector<short>>
checkBassins(std::vector<std::vector<short>> &valuesArray) {
  for (std::size_t i{}; i < std::size(valuesArray); ++i) {
    for (std::size_t j{}; j < lineLength; ++j) {

      if (valuesArray[i][j] < 0) {

        if (i < std::size(valuesArray) && j + 1 < lineLength) {
          if (valuesArray[i][j + 1] != 9 && valuesArray[i][j + 1] >= 0) {
            if (valuesArray[i][j + 1] == 0) {
              valuesArray[i][j] = shortMinCapacity;
            } else {
              valuesArray[i][j] = -valuesArray[i][j];
            }
          }
        }
        if (i < std::size(valuesArray) && j - 1 < lineLength) {
          if (valuesArray[i][j - 1] != 9 && valuesArray[i][j - 1] >= 0) {
            if (valuesArray[i][j - 1] == 0) {
              valuesArray[i][j - 1] = shortMinCapacity;
            } else {
              valuesArray[i][j - 1] = -valuesArray[i][j - 1];
            }
          }
        }
        if (i + 1 < std::size(valuesArray) && j < lineLength) {
          if (valuesArray[i + 1][j] != 9 && valuesArray[i][j + 1] >= 0) {
            if (valuesArray[i + 1][j] == 0) {
              valuesArray[i + 1][j] = shortMinCapacity;
            } else {
              valuesArray[i + 1][j] = -valuesArray[i + 1][j];
            }
          }
        }

        if (i - 1 < std::size(valuesArray) && j < lineLength) {
          if (valuesArray[i - 1][j] != 9 && valuesArray[i][j - 1] >= 0) {
            if (valuesArray[i - 1][j] == 0) {
              valuesArray[i - 1][j] = shortMinCapacity;
            } else {
              valuesArray[i - 1][j] = -valuesArray[i - 1][j];
            }
          }
        }
      }
    }
  }

  // move semantic
  return valuesArray;
}

int main() {

  std::ifstream input{"input.txt"};

  std::string strInput;
  std::vector<std::vector<short>> valuesArray{};
  valuesArray.reserve(100);

  while (std::getline(input, strInput)) {
    std::cout << strInput << '\n';

    std::vector<short> line{};
    line.reserve(lineLength);

    for (char value : strInput) {
      line.emplace_back(value - 48);
    }

    valuesArray.emplace_back(line);
  }

  valuesArray = setValues(valuesArray);

  std::vector<std::vector<short>> newValuesArray{};
  newValuesArray.reserve(100);

  while (true) {
    newValuesArray = checkBassins(valuesArray);
    if (newValuesArray == valuesArray) {
      break;
    }

    valuesArray = newValuesArray;
  }

  for (std::vector<short> line : newValuesArray) {
    for (short value : line) {
      std::cout << value << ' ';
    }

    std::cout << '\n';
  }
}
