#include <fstream>
#include <iostream>
#include <string>

std::ifstream &getFile();
void iterateOnFile(std::ifstream &inf);
void printTotalCalories(std::string &strInput);

int main() { iterateOnFile(getFile()); }

std::ifstream &getFile() {
  static std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "Unable to open file.";
  }

  return inf;
}

void iterateOnFile(std::ifstream &inf) {

  std::string strInput;

  while (std::getline(inf, strInput)) {
    printTotalCalories(strInput);
  }
}

void printTotalCalories(std::string &strInput) {

  static int calories{};

  if (strInput.empty()) {
    std::cout << calories << '\n';
    calories = 0;
  } else {
    calories += std::stoi(strInput);
  }
}
