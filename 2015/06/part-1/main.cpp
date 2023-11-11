#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>

int main() {
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::string strInput;
  std::regex pattern(
      "(turn on|turn off|toggle) ([0-9]+),([0-9]+) through ([0-9]+),([0-9]+)");
  std::smatch matches;

  std::array<std::array<int, 1000>, 1000> grid{};

  while (std::getline(inf, strInput, '\n')) {
    if (std::regex_search(strInput, matches, pattern)) {
      std::string action{matches[1]};
      std::pair<size_t, size_t> startingCoord{std::stoul(matches[2]),
                                              std::stoul(matches[3])};
      std::pair<size_t, size_t> endingCoord{std::stoul(matches[4]),
                                            std::stoul(matches[5])};

      // I don't know if there's any compiler optimization that allow to
      // remember the result of a condition through multiple loops
      if (action == "turn on") {
        for (std::size_t i{startingCoord.first}; i <= endingCoord.first; ++i) {
          for (std::size_t j{startingCoord.second}; j <= endingCoord.second;
               ++j) {
            ++grid[i][j];
          }
        }
      } else if (action == "turn off") {
        for (std::size_t i{startingCoord.first}; i <= endingCoord.first; ++i) {
          for (std::size_t j{startingCoord.second}; j <= endingCoord.second;
               ++j) {
            if (grid[i][j] > 0) {
              --grid[i][j];
            }
          }
        }
      } else if (action == "toggle") {
        for (std::size_t i{startingCoord.first}; i <= endingCoord.first; ++i) {
          for (std::size_t j{startingCoord.second}; j <= endingCoord.second;
               ++j) {
            grid[i][j] += 2;
          }
        }
      }
    } else {
      std::cerr << "Unable to find match.";
      return EXIT_FAILURE;
    }
  }

  int counter{};
  for (std::array<int, 1000> row : grid) {
    for (int light : row) {
      counter += light;
    }
  }
  std::cout << counter;

  return EXIT_SUCCESS;
}
