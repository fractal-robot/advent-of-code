#include <fstream>
#include <iostream>
int main() {
  std::ifstream inf{"input.txt"};
  if (!inf.is_open()) {
    std::cerr << "Unable to open file.";
  }
}
