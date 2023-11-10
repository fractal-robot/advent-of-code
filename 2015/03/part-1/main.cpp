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

  std::pair<int, int> cursorPos{0, 0};
  houses.insert(cursorPos);

  for (char c : strInput) {

    switch (c) {
    case '^':
      ++cursorPos.first;
      break;
    case 'v':
      --cursorPos.first;
      break;
    case '>':
      ++cursorPos.second;
      break;
    case '<':
      --cursorPos.second;
      break;
    }

    houses.insert(cursorPos);
  }
  std::cout << std::size(houses);
  return EXIT_SUCCESS;
}
