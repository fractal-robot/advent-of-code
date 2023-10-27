#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

int calculatePoints(std::string_view round) {

  enum Played {
    rock,
    paper,
    scissors,
  };

  // using ASCII table to resolve to the score for the shape
  int player{round[0] - 64};
  int opponent{round[2] - 87};

  // assert(round[0] == 0);
  // assert(round[2] == 0);
  //  then using enumeration to find easily who is the winner of the round
  enum State {
    loss = 0,
    draw = 3,
    win = 6,
  };

  State state{};

  if (player == opponent)
    state = draw;
  else if ((player == 1 && opponent == 3) || (player == 3 && opponent == 2) ||
           (player == 2 && opponent == 1))
    state = loss;
  else
    state = win;

  std::cout << player << " - " << opponent << '\t' << state << '\n';

  return state + player;
}

int main() {
  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  static std::string strInput;

  int pointNumber{};

  while (std::getline(inf, strInput)) {
    pointNumber += calculatePoints(strInput);
  }

  std::cout << pointNumber;
}
