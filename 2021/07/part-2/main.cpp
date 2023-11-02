#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Coordinates {

public:
  Coordinates(std::vector<int> &coordinates) : m_coordinates(coordinates) {
    std::cout << "Class Coordinates initialized." << '\n';
  }

  void calculateBestPos() {
    findMinMax();

    int minFuel{0};
    int pos{};

    for (std::size_t i = minMax.first; i <= minMax.second; ++i) {
      int fuel = calculateDistance(i);

      if (fuel < minFuel || minFuel == 0) {
        minFuel = fuel;
        pos = i;
      }
    }

    std::cout << minFuel << " -> " << pos;
  }

private:
  void findMinMax() {
    for (int i : m_coordinates) {
      if (i < minMax.first) {
        minMax.first = i;
      } else if (i > minMax.second) {
        minMax.second = i;
      }
    }
  }

  int calculateDistance(int pos) {
    int distance{};

    for (int coordinate : m_coordinates) {
      if (coordinate < pos) {
        distance += (pos - coordinate);
      } else if (coordinate > pos) {
        distance += (coordinate - pos);
      }
    }

    return distance;
  }

private:
  std::vector<int> m_coordinates;

  std::pair<int, int> minMax{};
};

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "Unable to open file.";
  }

  std::vector<int> coordinates{};
  coordinates.reserve(50);

  std::string strInput;
  if (std::getline(inf, strInput)) {
    std::istringstream iss(strInput);

    std::string token;
    while (std::getline(iss, token, ',')) {
      coordinates.emplace_back(std::stoi(token));
    }
  }

  Coordinates position{coordinates};
  position.calculateBestPos();
}
