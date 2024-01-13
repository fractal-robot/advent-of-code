#include <array>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<char> &findValues(const std::string &line) {
  std::array<std::string, 9> numbers{
      "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
  };

  static std::vector<char> values{};
  values.clear();
  values.reserve(5);

  for (std::size_t i{0}; i < std::size(line); ++i) {
    if (std::isdigit(line[i])) {
      values.push_back(line[i]);
    }
    for (std::size_t j{0}; j < std::size(numbers); ++j) {
      int counter{0};
      for (std::size_t k{0}; k < std::size(numbers[j]); ++k) {
        if (i + k <= std::size(line) && line[i + k] == numbers[j][k])
          ++counter;
      }
      if (counter == std::size(numbers[j]))
        values.push_back(j + 1 + 48);
    }
  }
  return values;
}

int main() {
  std::ifstream file{"input.txt"};
  if (!file.is_open()) {
    std::cerr << "Unable to open input file.";
  }
  std::string strInput;
  int sum{};
  while (std::getline(file, strInput, '\n')) {
    std::vector<char> values{findValues(strInput)};
    std::string localSum{std::string(1, values[0]) +
                         std::string(1, values[std::size(values) - 1])};
    sum += std::stoi(localSum);
  }

  std::cout << sum;
  return EXIT_SUCCESS;
}
