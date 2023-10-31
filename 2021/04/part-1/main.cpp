// using negative number to avoid creating boolean 2 dimentionnal arrays

#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

constexpr std::size_t boardSize{5};

using Board = std::array<std::array<int, boardSize>, boardSize>;
using BoardsVector = std::vector<Board>;

// can't use std::string_view with constructor of std::istringstream
std::vector<int> &getValuesArray(const std::string &strInput) {
  static std::vector<int> values{};
  values.reserve(100);

  std::istringstream iss(strInput);
  std::string token;
  while (std::getline(iss, token, ',')) {
    int value = std::stoi(token);
    values.push_back(value);
  }

  return values;
}

// can't use std::string_view with constructor of std::istringstream
std::array<int, boardSize> stringToArray(const std::string &strInput) {

  std::array<int, boardSize> array{};
  std::istringstream iss(strInput);

  for (std::size_t i = 0; i < boardSize; i++) {
    iss >> array[i];
  }

  for (int i : array) {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  return array;
}

void printBoards(const BoardsVector &boards) {

  for (const Board &board : boards) {
    for (const auto &arow : board) {
      for (const auto &e : arow) {
        std::cout << e << '\t';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
}

void getBingoBoards(const std::string &strInput, Board &board,
                    BoardsVector &boards) {
  static std::size_t counter;
  static Board voidBoard{};

  if (strInput.empty()) {
    if (board != voidBoard) {
      counter = 0;
      // so a new line is necessary at the end of the input file
      boards.push_back(board);
      board = voidBoard;
    }
  } else {
    board[counter] = stringToArray(strInput);

    ++counter;
  }
}

int main() {

  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;
  bool firstI{true};

  std::vector<int> *values;

  static BoardsVector boards{};
  boards.reserve(50);

  static Board board{0};

  while (std::getline(inf, strInput)) {
    if (firstI) {
      values = &getValuesArray(strInput);
      firstI = false;
    } else {
      // change board and boards
      getBingoBoards(strInput, board, boards);
    }
  }

  std::cout << "\n\n\n";
  printBoards(boards);

  for (int i : *values) {
    std::cout << i << ' ';
  }

  return EXIT_SUCCESS;
}

// return by CONST reference
