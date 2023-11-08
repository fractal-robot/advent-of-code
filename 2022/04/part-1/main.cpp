#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct Pair {
  std::vector<int> v1{};
  std::vector<int> v2{};
};

std::vector<int> getInterval(std::string strInput) {
  std::pair<std::string, std::string> interval;

  std::istringstream iss{strInput};
  std::getline(iss, interval.first, '-');
  std::getline(iss, interval.second);

  std::vector<int> valuesList{};
  valuesList.reserve(std::stoul(interval.second));

  for (std::size_t i{std::stoul(interval.first)};
       i <= std::stoul(interval.second); ++i) {
    valuesList.emplace_back(i);
  }

  return valuesList;
}

void countFullyContained(std::vector<Pair> &pairs) {
  int counter{};

  for (Pair pair : pairs) {
    for (int value1 : pair.v1) {
      if ((value1 >= pair.v2[0] && value1 <= pair.v2[std::size(pair.v2)])) {
        break;
      }
      ++counter;
    }
    for (int value2 : pair.v2) {
      if ((value2 >= pair.v1[0] && value2 <= pair.v1[std::size(pair.v1)])) {
        break;
      }
      ++counter;
    }
  }

  std::cout << '\n' << counter;
}

int main() {

  std::ifstream input{"input.txt"};
  std::string strInput;

  std::vector<Pair> pairs{};
  pairs.reserve(100);

  while (std::getline(input, strInput)) {
    Pair pair{};

    pair.v1 = getInterval(strInput.substr(0, strInput.find(',')));
    pair.v2 = getInterval(strInput.substr(strInput.find(',') + 1));
    pairs.emplace_back(pair);
  }

  countFullyContained(pairs);

  return EXIT_SUCCESS;
}
