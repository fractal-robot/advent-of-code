#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum Direction {
  forward,
  down,
  up,
};

//
void evalCoord(Direction direction, int greatness);
//

void getData() {
  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;

  std::string word;
  int number;

  while (std::getline(inf, strInput)) {

    std::istringstream lineStream(strInput);

    lineStream >> word;
    lineStream >> number;

    std::cout << word << ' ' << number << '\n';

    Direction direction;
    if (word == "forward") {
      direction = forward;
    } else if (word == "down") {
      direction = down;
    } else if (word == "up") {
      direction = up;
    }

    evalCoord(direction, number);
  }
}

int main() {
  getData();
  return EXIT_SUCCESS;
}

void evalCoord(Direction direction, int greatness) {
  struct Position {
    int x{0};
    int y{0};
  };

  Position actual{};

  // static Position total{};

  switch (direction) {
  case forward:
    actual.x += greatness;
    break;
  case up:
    actual.y += greatness;
    break;
  case down:
    actual.y -= greatness;
    break;
  }

  std::cout << '\n'
            << "actual position: " << actual.x << ' ' << actual.y << '\n';
}
