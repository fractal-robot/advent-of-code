#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class Lanternfish {

public:
  Lanternfish(std::array<long int, 9> &internalStates)
      : m_internalStates{internalStates} {
    std::cout << "Class Lanternfish initialized." << '\n';
  }

  void addDay() {
    ++m_day;
    setNewState();
  }

  void printTotal() {
    long int total{0};

    for (long int i : m_internalStates) {
      total += i;
    }
    std::cout << total;
  }

private:
  void setNewState() {
    long int firstElement{m_internalStates[0]};
    m_internalStates[9] = firstElement;
    m_internalStates[7] += firstElement;

    for (std::size_t i{}; i < std::size(m_internalStates); ++i) {
      m_internalStates[i] = m_internalStates[i + 1];
    }
  }

private:
  std::array<long int, 9> m_internalStates{};
  int m_day{0};
};

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "Unable to open file.";
  }

  std::string strInput;
  std::array<long int, 9> internalStates{};

  if (std::getline(inf, strInput)) {
    std::istringstream iss(strInput);
    std::string token;

    while (std::getline(iss, token, ',')) {
      int value = std::stoi(token);
      internalStates[static_cast<std::size_t>(value)] += 1;
    }
  }

  int passedDays{256};

  Lanternfish lanternfish{internalStates};

  for (long int i{0}; i < passedDays; ++i) {
    lanternfish.addDay();
  }

  lanternfish.printTotal();

  return EXIT_SUCCESS;
}
