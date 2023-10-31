#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int byteSize{5}; // 12

using BytesArray = std::vector<std::bitset<byteSize>>;
static BytesArray bytes{};

std::vector<int> occurrencesOf0(byteSize);
std::vector<int> occurrencesOf1(byteSize);

std::bitset<byteSize> sumOccurencesOf0{};
std::bitset<byteSize> sumOccurencesOf1{};

//

void createOccurrencesVectors(std::string_view strInput) {
  std::size_t index{0};

  for (char c : strInput) {
    switch (c) {
    case '0':
      occurrencesOf0[index] += 1;
      break;
    case '1':
      occurrencesOf1[index] += 1;
      break;
    }
    ++index;
  }
}

void printOccurrences(std::vector<int> vector0, std::vector<int> vector1) {

  for (int i : vector0) {
    std::cout << i;
  }

  std::cout << ' ';
  for (int i : vector1) {
    std::cout << i;
  }

  std::cout << '\n';
}

//

std::bitset<byteSize> stringToBitset(std::string_view string) {
  std::bitset<byteSize> byte{};
  std::size_t i{0};

  for (char c : string) {
    if (c == '1')
      byte.set(byteSize - i - 1);
    ++i;
  }

  return byte;
}

void getMostCommonValue(std::size_t index) {

  if ((occurrencesOf1[index] / std::pow(10, byteSize)) <
      (occurrencesOf0[index] / std::pow(10, byteSize))) {
    sumOccurencesOf0.set(byteSize - index - 1);
  }
}

int main() {

  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;
  while (std::getline(inf, strInput)) {
    createOccurrencesVectors(strInput);

    std::bitset<byteSize> byte{stringToBitset(strInput)};
    bytes.reserve(100);
    bytes.push_back(stringToBitset(strInput));
  }

  printOccurrences(occurrencesOf0, occurrencesOf1);

  // find the bit criteria
  for (std::size_t i{0}; i < byteSize; ++i) {
    getMostCommonValue(i);
  }

  std::cout << sumOccurencesOf0 << ' ';
  sumOccurencesOf1 = ~sumOccurencesOf0;
  std::cout << sumOccurencesOf1;

  return EXIT_SUCCESS;
}

void findRatings(std::bitset<byteSize> occurences, int position) {
  BytesArray sortingBytes{bytes};

  std::bitset<byteSize> byte{};

  for (std::size_t j{0}; j < std::size(sortingBytes); ++j) {

    byte = sortingBytes[j];

    if (byte.test(byteSize - position - 1) !=
        occurences.test(byteSize - position - 1)) {
    }
  }
}
