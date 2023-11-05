#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using Shapes = std::pair<int, int>;

class HandShapes {
public:
  static void addToScoreboard(Shapes shape) {
    if (shape.first == shape.second) {
      scoreMe += 3;
      scoreOpponent += 3;
    } else if ((shape.first == 1 && shape.second == 3) ||
               (shape.first == 3 && shape.second == 2) ||
               (shape.first == 2 && shape.second == 1)) {
      scoreOpponent += 6;
    } else {
      scoreMe += 6;
    }

    scoreMe += shape.second;
    scoreOpponent += shape.first;
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
