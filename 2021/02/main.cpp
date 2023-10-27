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

struct Position {
  int x{0};
  int y{0};

  Position &operator+=(const Position &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
};

//
void getData();
Position evalCoord(Direction direction, int greatness);
//

int main() {
  getData(); // also call evalCoord, and print result

  return EXIT_SUCCESS;
}

void getData() {
  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;

  std::string word;
  int number;

  static Position total{};

  while (std::getline(inf, strInput)) {

    std::istringstream lineStream(strInput);

    lineStream >> word;
    lineStream >> number;

    Direction direction;
    if (word == "forward") {
      direction = forward;
    } else if (word == "down") {
      direction = down;
    } else if (word == "up") {
      direction = up;
    }

    total += evalCoord(direction, number);
  }

  std::cout << total.x * total.y;
}

Position evalCoord(Direction direction, int greatness) {
  Position actual{};

  switch (direction) {
  case forward:
    actual.x += greatness;
    break;
  case up:
    actual.y -= greatness;
    break;
  case down:
    actual.y += greatness;
    break;
  }

  return actual;
}
