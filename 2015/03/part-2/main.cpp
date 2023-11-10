#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    return h1 ^ h2;
  }
};

int main() {
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::string strInput;
  std::getline(inf, strInput, '\n');

  std::unordered_set<std::pair<int, int>, pair_hash> houses;

  std::pair<int, int> santaCursorPos{0, 0};
  std::pair<int, int> robotCursorPos{0, 0};

  houses.insert(santaCursorPos);

  bool firstI{true};

  for (char c : strInput) {

    switch (c) {
    case '^':
      if (firstI) {
        ++santaCursorPos.first;
      } else {
        ++robotCursorPos.first;
      }
      break;
    case 'v':
      if (firstI) {
        --santaCursorPos.first;
      } else {
        --robotCursorPos.first;
      }
      break;
    case '>':
      if (firstI) {
        ++santaCursorPos.second;
      } else {
        ++robotCursorPos.second;
      }
      break;
    case '<':
      if (firstI) {
        --santaCursorPos.second;
      } else {
        --robotCursorPos.second;
      }
      break;
    }

    if (firstI) {
      firstI = false;
    } else {
      firstI = true;
    }

    houses.insert(santaCursorPos);
    houses.insert(robotCursorPos);
  }
  std::cout << std::size(houses);
  return EXIT_SUCCESS;
}
