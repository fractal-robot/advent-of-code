// using negative number to avoid creating boolean 2 dimentionnal arrays

#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

constexpr std::size_t boardSize{5};

using Board = std::array<std::array<int, boardSize>, boardSize>;
using BoardsVector = std::vector<Board>;

static Board emptyBoard{};

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

std::array<int, boardSize> stringToArray(const std::string &strInput) {

  std::array<int, boardSize> array{};
  std::istringstream iss(strInput);

  for (std::size_t i = 0; i < boardSize; i++) {
    iss >> array[i];
  }
  return array;
}

void getBingoBoards(const std::string &strInput, Board &board,
                    BoardsVector &boards) {
  static std::size_t counter;

  if (strInput.empty()) {
    if (board != emptyBoard) {
      counter = 0;
      // so a new line is necessary at the end of the input file
      boards.push_back(board);
      board = emptyBoard;
    }
  } else {
    board[counter] = stringToArray(strInput);

    ++counter;
  }
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

//

int markNumbers(std::vector<int> *values, BoardsVector &boards) {
  int value = (*values)[0];

  for (std::size_t board{0}; board < std::size(boards); ++board) {
    for (std::size_t arow{0}; arow < std::size(boards[0]); ++arow) {
      for (std::size_t e{0}; e < std::size(boards[0][0]); ++e) {
        if (boards[board][arow][e] == value) {
          boards[board][arow][e] = -(boards[board][arow][e]);
          std::cout << "value " << value << " has been removed" << '\n';
        }
      }
    }
  }

  values->erase(values->begin());
  return value;
}

bool checkRows(Board &board) {
  for (std::size_t row = 0; row < boardSize; row++) {
    bool allNegative = true;
    for (std::size_t col = 0; col < boardSize; col++) {
      if (board[row][col] >= 0) {
        allNegative = false;
        break;
      }
    }
    if (allNegative) {
      return true;
    }
  }

  return false;
}

bool checkColumns(Board &board) {
  for (std::size_t col = 0; col < boardSize; col++) {
    bool allNegative = true;
    for (std::size_t row = 0; row < boardSize; row++) {
      if (board[row][col] >= 0) {
        allNegative = false;
        break;
      }
    }
    if (allNegative) {
      return true;
    }
  }

  return false;
}

void checkForWinner(BoardsVector &boards) {
  for (std::size_t board{0}; board < std::size(boards); ++board) {
    if (checkRows(boards[board]) || checkColumns(boards[board])) {
      boards.erase(boards.begin() + static_cast<int>(board));
      std::cout << "a board have been removed" << '\n';
    }
  }
}

int calculateWinningBoardScore(Board board, int calledNumber) {

  int sum{0};
  for (std::size_t row{0}; row < boardSize; ++row) {
    for (std::size_t col{0}; col < boardSize; ++col) {
      if (board[row][col] > 0) {
        sum += board[row][col];
      }
    }
  }
  std::cout << sum << " * " << calledNumber << " = " << sum * calledNumber;
  return sum;
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

  static Board board{};

  while (std::getline(inf, strInput)) {
    if (firstI) {
      values = &getValuesArray(strInput);
      firstI = false;
    } else {
      // change board and boards
      getBingoBoards(strInput, board, boards);
    }
  }

  int calledNumber;

  while (!values->empty()) {

    checkForWinner(boards);

    if (std::size(boards) == 1) {
      std::cout << "breaking loop" << '\n';
      calledNumber = markNumbers(values, boards);

      break;
    }

    // also change values and boards
    calledNumber = markNumbers(values, boards);

    std::cout << "there is " << std::size(boards) << " before " << calledNumber
              << '\n';

    std::cout << "there is " << std::size(boards) << " after " << calledNumber
              << '\n';
  }

  std::cout << std::size(boards) << '\n';
  printBoards(boards);
  calculateWinningBoardScore(boards[0], calledNumber);

  return EXIT_SUCCESS;
}
