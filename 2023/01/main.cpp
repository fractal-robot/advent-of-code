#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> &getSortedData() {
  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  static std::vector<int> stackCalories{};
  stackCalories.reserve(100);

  std::string strInput;
  int calories{};

  while (std::getline(inf, strInput)) {

    if (strInput.empty()) {
      stackCalories.emplace_back(calories);
      calories = 0;
    } else {
      calories += std::stoi(strInput);
    }
  }

  int max{};

  for (int i : stackCalories) {
    max += i;
  }

  // could have been done better
  std::sort(stackCalories.begin(), stackCalories.end());

  return stackCalories;
}

int main() {
  std::vector<int> calories{getSortedData()};

  const unsigned long size{calories.size()};

  std::cout << "max calories: " << calories[size - 1] << '\n';
  std::cout << "max calories x3: "
            << calories[size - 1] + calories[size - 2] + calories[size - 3]
            << '\n';
}
