#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Coordinates = std::array<int, 4>;
using Map = std::vector<std::vector<int>>;

class Data {

public:
  void extractValues(std::string &strInput) {
    std::size_t separator = strInput.find(" -> ");
    strInput.replace(separator, 4, ",");

    std::istringstream iss(strInput);
    std::string token;

    std::size_t i{0};
    while (std::getline(iss, token, ',')) {
      coordinates[i] = std::stoi(token);
      ++i;
    }

    if (checkOneLine()) {
      coordinatesList.emplace_back(coordinates);
    }
  }

  void setMaxCoordinates() {
    for (Coordinates coor : coordinatesList) {

      if (coor[0] > xMax) {
        xMax = coor[0];
      }
      if (coor[2] > xMax) {
        xMax = coor[2];
      }
      if (coor[1] > yMax) {
        yMax = coor[1];
      }
      if (coor[3] > yMax) {
        yMax = coor[3];
      }
    }

    std::cout << "Max coordinates: " << xMax << ", " << yMax << '\n';
  }

  void drawMap() {

    for (Coordinates coor : coordinatesList) {
      if (coor[0] == coor[2]) {
        drawVerticalLine(coor);
      } else if (coor[1] == coor[3]) {
        drawHorizontalLine(coor);
      }
    }
  }

private:
  bool checkOneLine() {

    if (coordinates[0] == coordinates[2] || coordinates[1] == coordinates[3]) {
      return true;
    }

    return false;
  }

  void drawVerticalLine(Coordinates &coor) { ; }

  void drawHorizontalLine(Coordinates &coor) { ; }

private:
  Coordinates coordinates;
  std::vector<Coordinates> coordinatesList;

  std::pair<int, int> maxCoordinates;

  int xMax{};
  int yMax{};

  Map map{};
};

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  Data data{};

  std::string strInput;
  while (std::getline(inf, strInput)) {
    data.extractValues(strInput);
  }

  data.setMaxCoordinates();
}
