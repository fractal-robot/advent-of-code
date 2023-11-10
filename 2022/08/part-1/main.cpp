#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

constexpr int numRows{5};

int main() {
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::vector<std::vector<short>> treeMap{};

  std::string strInput;
  while (std::getline(inf, strInput, '\n')) {
    std::vector<short> colTreeMap{};
    for (char c : strInput) {
      colTreeMap.emplace_back(c - 48);
    }

    treeMap.emplace_back(colTreeMap);
  }

  for (std::vector<short> vector : treeMap) {
    for (short i : vector) {
      std::cout << i << ' ';
    }

    std::cout << '\n';
  }

  int counter{};
  int counterExterior{};
  for (std::size_t i{0}; i < std::size(treeMap); ++i) {
    for (std::size_t j{0}; j < std::size(treeMap[0]); ++j) {
      if (j == 0 || j == std::size(treeMap[0]) - 1 || i == 0 ||
          i == std::size(treeMap[0]) - 1) {
        counterExterior++;
      } else {

        // check up

        bool clearUp{false};
        bool clearDown{false};
        bool clearRight{false};
        bool clearLeft{false};

        for (std::size_t iTesterUp{i - 1}; iTesterUp > 0; --iTesterUp) {
          if (treeMap[iTesterUp][j] > treeMap[i][j]) {
            clearUp = false;
            break;
          }
          clearUp = true;
        }

        for (std::size_t iTesterDown{i + 1}; iTesterDown < std::size(treeMap);
             iTesterDown++) {
          if (treeMap[iTesterDown][j] > treeMap[i][j]) {
            clearUp = false;
            break;
          }
          clearUp = true;
        }

        for (std::size_t jTesterLeft{j - 1}; jTesterLeft > 0; --jTesterLeft) {
          if (treeMap[i][jTesterLeft] > treeMap[i][j]) {
            clearLeft = false;
            break;
          }
          clearLeft = true;
        }
        for (std::size_t jTesterRight{j + 1};
             jTesterRight >= std::size(treeMap[0]); --jTesterRight) {
          if (treeMap[i][jTesterRight] > treeMap[i][j]) {
            clearRight = false;
            break;
          }
          clearRight = true;
        }

        if (!(clearUp && clearDown && clearRight && clearLeft)) {
          ++counter;
          std::cout << '\n'
                    << treeMap[i][j] << ' ' << i << ' ' << j << " is clear.";
        }
      }
    }
  }

  std::cout << counter << ' ' << counterExterior;
}
