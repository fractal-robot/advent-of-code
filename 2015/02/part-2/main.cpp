#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Box = std::vector<int>;

int getValue(Box &box) {

  int sum{};

  std::sort(box.begin(), box.end());
  sum += box[0] * 2 + box[1] * 2;
  sum += box[0] * box[1] * box[2];

  return sum;
}

int main() {
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::string strInput;
  int sum{0};

  while (std::getline(inf, strInput, '\n')) {

    std::istringstream iss{strInput};
    std::string token;

    Box box{};

    while (std::getline(iss, token, 'x')) {
      box.emplace_back(std::stoi(token));
    }

    sum += getValue(box);
  }

  std::cout << sum;
}
