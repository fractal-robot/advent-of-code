#include <algorithm>
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

// ---

class Coor {
public:
  std::pair<int, int> getMaxCoordinates() const {
    std::pair maxCoordinates(xMax, yMax);
    return maxCoordinates;
  }

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
        // std::cout << i << ' ';
      }
      // std::cout << '\n';
    }

    // std::cout << '\n';
  }

  std::vector<std::vector<int>> &getCoordinatesSets() {

    static std::vector<std::vector<int>> coorList{};
    coorList.reserve(50);

    for (Coordinates coor : coordinatesList) {
      coordinatesSet.erase(coordinatesSet.begin(), coordinatesSet.end());

      if (coor[0] == coor[2]) {
        generateXLine(coor);
      } else if (coor[1] == coor[3]) {
        generateYLine(coor);
      } else {
        std::cerr << "invalid coordinates" << '\n';
      }

      for (int i : coordinatesSet) {
        // std::cout << i << ' ';
      }

      // std::cout << '\n';
      coorList.emplace_back(coordinatesSet);
    }

    return coorList;
  }

private:
  bool checkOneLine() {

    if (coordinates[0] == coordinates[2] || coordinates[1] == coordinates[3]) {
      return true;
    }

    return false;
  }

  void generateXLine(Coordinates &coor) {
    // treated as a boolean value to know direction (x, y)
    coordinatesSet.emplace_back(0);

    coordinatesSet.emplace_back(coor[0]);

    if (coor[1] <= coor[3]) {
      for (int i{coor[1]}; i <= coor[3]; ++i) {
        coordinatesSet.emplace_back(static_cast<std::size_t>(i));
      }
    }
    if (coor[1] >= coor[3]) {
      for (int i{coor[3]}; i <= coor[1]; ++i) {
        coordinatesSet.emplace_back(static_cast<std::size_t>(i));
      }
    }
  }

  void generateYLine(Coordinates &coor) {
    // treated as a boolean value to know direction (x, y)
    coordinatesSet.emplace_back(1);

    coordinatesSet.emplace_back(coor[1]);

    if (coor[0] <= coor[2]) {
      for (int i{coor[0]}; i <= coor[2]; ++i) {
        coordinatesSet.emplace_back(static_cast<std::size_t>(i));
      }
    }

    if (coor[0] >= coor[2]) {
      for (int i{coor[2]}; i <= coor[0]; ++i) {
        coordinatesSet.emplace_back(static_cast<std::size_t>(i));
      }
    }
  }

private:
  Coordinates coordinates;
  std::vector<Coordinates> coordinatesList;

  int xMax{};
  int yMax{};

  std::vector<int> coordinatesSet{};

  std::vector<std::vector<int>> map;
};

// ---

class Map {
public:
  Map(std::pair<int, int> max)
      : xMax(max.first), yMax(max.second),
        map(static_cast<std::size_t>(xMax + 1),
            std::vector<int>(static_cast<std::size_t>(yMax + 1))) {
    std::cout << "Class map initialized." << '\n';
  }

  void createMap(std::vector<std::vector<int>> &coordsList) {
    std::cout << '\n' << "in map" << '\n';
    for (std::vector<int> values : coordsList) {
      if (values[0] == 0) {
        drawYLine(values);

      } else if (values[0] == 1) {
        drawXLine(values);
      } else {
        std::cerr << "Unable to find value direction.";
      }
    }
  }

  void printMap() {
    int counter{0};

    for (std::vector<int> axis : map) {
      for (int value : axis) {
        if (value == 2) {
          ++counter;
        }
        if (value == 0) {
          std::cout << '.';
        } else {

          std::cout << value;
        }
      }
      std::cout << '\n';
    }
    std::cout << '\n' << counter << '\n';
  }

  void test_calculateSums(std::vector<std::vector<int>> &coordsList) {
    int coordinatesSum{0};
    int mapSum{0};

    for (std::vector<int> values : coordsList) {
      coordinatesSum += static_cast<int>(std::size(values)) - 2;
    }

    for (std::vector<int> axis : map) {
      for (int value : axis) {
        mapSum += value;
      }
    }

    std::cout << coordinatesSum << ' ' << mapSum << '\n';
  }

private:
  void drawXLine(const std::vector<int> &values) {
    if (values.size() < 4) {
      std::cerr << "Invalid input data for drawing X-line." << std::endl;
      return; // Exit early to avoid invalid access.
    }

    const std::size_t row = static_cast<std::size_t>(values[1]);
    const std::size_t minCol = static_cast<std::size_t>(values[2]);
    const std::size_t maxCol = static_cast<std::size_t>(values.back());

    if (row < map.size()) {
      for (std::size_t col = std::max<std::size_t>(minCol, 0U);
           col <= std::min<std::size_t>(maxCol, map[row].size() - 1); ++col) {
        map[row][col] += 1;
      }
    }
  }

  void drawYLine(const std::vector<int> &values) {
    if (values.size() < 4) {
      std::cerr << "Invalid input data for drawing Y-line." << std::endl;
      return; // Exit early to avoid invalid access.
    }

    const std::size_t col = static_cast<std::size_t>(values[1]);
    const std::size_t minRow = static_cast<std::size_t>(values[2]);
    const std::size_t maxRow = static_cast<std::size_t>(values.back());

    if (col < map[0].size()) {
      for (std::size_t row = std::max<std::size_t>(minRow, 0U);
           row <= std::min<std::size_t>(maxRow, map.size() - 1); ++row) {
        map[row][col] += 1;
      }
    }
  }

private:
  int xMax{};
  int yMax{};

  std::vector<std::vector<int>> map{};
};

// ---

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "unable to open file.";
  }

  Coor coord{};

  std::string strInput;
  while (std::getline(inf, strInput)) {
    coord.extractValues(strInput);
  }

  coord.setMaxCoordinates();

  std::vector<std::vector<int>> coordsList{coord.getCoordinatesSets()};
  std::pair maxCoord{coord.getMaxCoordinates()};

  if (maxCoord.first < 1 || maxCoord.second < 1) {
    std::cerr << "Invalid max coordinates";
  }

  Map map{maxCoord};
  map.createMap(coordsList);
  map.test_calculateSums(coordsList);
  map.printMap();
}
