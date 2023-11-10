#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Box = std::vector<int>;

int getValue(Box &box) {

  int smallestSize{};
  int sum{};

  std::array<int, 3> values{
      box[0] * box[1],
      box[1] * box[2],
      box[2] * box[0],
  };

  for (int i : values) {
    sum += i * 2;

    if (i < smallestSize || smallestSize == 0) {
      smallestSize = i;
    }
  }

  return sum + smallestSize;
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
