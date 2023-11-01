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

  void printCoordinates() {
    for (Coordinates coor : coordinatesList) {
      for (int i : coor) {
        std::cout << i << ' ';
      }
      std::cout << '\n';
    }

    std::cout << '\n';
  }

  void drawMap() {

    for (Coordinates coor : coordinatesList) {
      coordinatesSet.erase(coordinatesSet.begin(), coordinatesSet.end());
      generateCoordinatesSet(coor);

      for (int i : coordinatesSet) {
        std::cout << i << ' ';
      }

      std::cout << '\n';
    }
  }

private:
  bool checkOneLine() {

    if (coordinates[0] == coordinates[2] || coordinates[1] == coordinates[3]) {
      return true;
    }

    return false;
  }

  void generateCoordinatesSet(Coordinates &coor) {
    if (coor[0] == coor[2]) {
      generateXLine(coor);
    } else if (coor[1] == coor[3]) {
      generateYLine(coor);
    } else {
      std::cerr << "invalid coordinates" << '\n';
    }
  }

  void generateXLine(Coordinates &coor) {
    coordinatesSet.emplace_back(coor[0]);

    if (coor[1] <= coor[3]) {
      for (int i{coor[1]}; i <= coor[3]; ++i) {
        coordinatesSet.emplace_back(i);
      }
    }
    if (coor[1] >= coor[3]) {
      for (int i{coor[3]}; i <= coor[1]; ++i) {
        coordinatesSet.emplace_back(i);
      }
    }
  }

  void generateYLine(Coordinates &coor) {

    coordinatesSet.emplace_back(coor[1]);

    if (coor[0] <= coor[2]) {
      for (int i{coor[0]}; i <= coor[2]; ++i) {
        coordinatesSet.emplace_back(i);
      }
    }

    if (coor[0] >= coor[2]) {
      for (int i{coor[2]}; i <= coor[0]; ++i) {
        coordinatesSet.emplace_back(i);
      }
    }
  }

private:
  Coordinates coordinates;
  std::vector<Coordinates> coordinatesList;

  std::pair<int, int> maxCoordinates;

  int xMax{};
  int yMax{};

  std::vector<int> coordinatesSet{};

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
  data.printCoordinates();
  data.drawMap();
}
