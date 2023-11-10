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
  std::size_t counter{};
  bool isTreated{false};

  for (Pair pair : pairs) {
    for (int pair1 : pair.v1) {
      for (int pair2 : pair.v2) {
        if (pair1 == pair2 && isTreated == false) {
          counter++;
          isTreated = true;
        }
      }
    }
    isTreated = false;
  }
  std::cout << counter;
}

int main() {

  std::ifstream input{"input.txt"};
  if (!input) {
    std::cerr << "Unable to open file.";
  }

  std::string strInput;

  std::vector<Pair> pairs{};
  pairs.reserve(100);

  while (std::getline(input, strInput)) {
    Pair pair{};

    pair.v1 = getInterval(strInput.substr(0, strInput.find(',')));
    pair.v2 = getInterval(strInput.substr(strInput.find(',') + 1));

    for (int c : pair.v1) {
      std::cout << c << ' ';
    }

    std::cout << '\n';

    for (int c : pair.v2) {
      std::cout << c << ' ';
    }

    std::cout << '\n';

    pairs.emplace_back(pair);
  }

  countFullyContained(pairs);

  return EXIT_SUCCESS;
}
