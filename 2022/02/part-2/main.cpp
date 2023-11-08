#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Shapes = std::pair<int, int>;

class HandShapes {
public:
  static void addToScoreboard(Shapes shape) {
    constexpr std::array<std::pair<int, int>, 4> moves{
        {{1, 3}, {3, 2}, {2, 1}}};

    if (shape.second == 2) {
      scoreMe += 3 + shape.first;
      scoreOpponent += 3 + shape.first;

    } else if (shape.second == 1) {
      for (std::pair move : moves) {

        if (move.first == shape.first) {
          scoreMe += move.second;
          scoreOpponent += 6 + move.first;
        }
      }
    } else {
      for (std::pair move : moves) {
        if (move.second == shape.first) {
          scoreMe += 6 + move.first;
          scoreOpponent += move.second;
        }
      }
    }
  }

  inline static int scoreMe{};
  inline static int scoreOpponent{};
};

int main() {
  std::ifstream iff{"input.txt"};
  if (!iff) {
    std::cerr << "Unable to open file.";
  }

  std::string strInput;
  while (std::getline(iff, strInput)) {
    HandShapes::addToScoreboard(Shapes{strInput[0] - 64, strInput[2] - 87});
  }

  std::cout << HandShapes::scoreMe;
}
