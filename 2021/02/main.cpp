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
  int aim{0};

  // operator overloading is not needed anymore
  Position &operator+=(const Position &other) {
    x += other.x;
    y += other.y;
    aim += other.aim;
    return *this;
  }
};

//
void getData();
void evalCoord(Direction direction, int greatness);
//

int main() {
  getData(); // also call evalCoord, which print result

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

    evalCoord(direction, number);
  }
}

void evalCoord(Direction direction, int greatness) {
  static Position total{};

  switch (direction) {
  case forward:
    total.x += greatness;
    total.y += (greatness * total.aim);
    break;
  case up:
    total.aim -= greatness;
    break;
  case down:
    total.aim += greatness;
    break;
  }

  std::cout << total.x << '\t' << total.y << '\t' << total.aim << '\n';

  std::cout << '\n' << total.y * total.x;
}
