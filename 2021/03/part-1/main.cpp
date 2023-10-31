#include <algorithm>
#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

//
void createOccurrencesVectors(std::string string);
void printOccurrences(std::vector<int> vector, std::vector<int> vector1);
void getAndPrintGammaRateAndEpsilonRate(std::vector<int> vector0,
                                        std::vector<int> vector1);
//

constexpr int byteSize{12};
static std::vector<int> occurrencesOf0(byteSize);
static std::vector<int> occurrencesOf1(byteSize);

int main() {
  std::ifstream inf{"input.txt"};

  if (!inf) {
    std::cerr << "unable to open file.";
  }

  std::string strInput;

  while (std::getline(inf, strInput)) {
    createOccurrencesVectors(strInput);
  }

  printOccurrences(occurrencesOf0, occurrencesOf1);
  getAndPrintGammaRateAndEpsilonRate(occurrencesOf0, occurrencesOf1);

  return EXIT_SUCCESS;
}

void createOccurrencesVectors(std::string string) {

  std::size_t index{0};

  for (char c : string) {
    switch (c) {
    case '0':
      occurrencesOf0[index] += 1;
      break;
    case '1':
      occurrencesOf1[index] += 1;
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

void getAndPrintGammaRateAndEpsilonRate(std::vector<int> vector0,
                                        std::vector<int> vector1) {
  std::bitset<byteSize> gammaRate;

  for (std::size_t iterator{0}; iterator < byteSize; ++iterator) {
    if (vector1[iterator] > vector0[iterator]) {
      gammaRate.set(byteSize - iterator - 1);
    }
  }

  std::bitset<byteSize> elipsonRate{~gammaRate};

  std::cout << gammaRate << ' ' << elipsonRate << '\n';

  auto iGammaRate{static_cast<unsigned int>(gammaRate.to_ulong())};
  auto iElipsonRate{static_cast<unsigned int>(elipsonRate.to_ulong())};
  std::cout << '\n'
            << iGammaRate << " * " << iElipsonRate << " = "
            << iGammaRate * iElipsonRate;
}
