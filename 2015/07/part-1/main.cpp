#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct WireOperation {
  std::string operand1{};
  std::string operand2{};
  std::string oper{};
  std::string wire{};
};

bool isStringDigits(std::string_view str) {
  return std::all_of(str.begin(), str.end(),
                     [](char ch) { return std::isdigit(ch); });
}

int main() {
  // parse data
  std::ifstream inf{"input.txt"};
  if (!(inf.is_open())) {
    std::cerr << "Unable to open file.";
    return EXIT_FAILURE;
  }

  std::string strInput;
  std::regex pattern("([a-z10-9]*)\\s*([A-Z]*)\\s*([a-z0-9]*) -> ([a-z]+)");

  std::vector<WireOperation> operations{};
  operations.reserve(100);

  while (std::getline(inf, strInput)) {
    std::smatch matches;

    if (std::regex_match(strInput, matches, pattern)) {
      WireOperation operation{matches[1], matches[3], matches[2], matches[4]};
      operations.emplace_back(operation);
    } else {
      std::cerr << "Unable to find match for " << strInput << '.';
      return EXIT_FAILURE;
    }
  }

  // treat data
  std::unordered_map<std::string, int> wireValuesMap;

  for (WireOperation op : operations) {

    if (op.oper == "NOT") {
      if (wireValuesMap.count(op.operand2) > 0) {
        wireValuesMap[op.wire] = ~wireValuesMap[op.operand2];
      } else if (isStringDigits(op.operand2)) {
        wireValuesMap[op.wire] = ~std::stoi(op.operand2);
      }

    } else if (op.oper == "AND") {
      if (isStringDigits(op.operand1) && isStringDigits(op.operand2)) {
        wireValuesMap[op.wire] =
            std::stoi(op.operand1) & std::stoi(op.operand2);
      } else if (isStringDigits(op.operand1) &&
                 wireValuesMap.count(op.operand2) > 0) {
        wireValuesMap[op.wire] =
            std::stoi(op.operand1) & wireValuesMap[op.operand2];
      } else if (isStringDigits(op.operand2) &&
                 wireValuesMap.count(op.operand1) > 0) {
        wireValuesMap[op.wire] =
            std::stoi(op.operand2) & wireValuesMap[op.operand1];
      } else if (wireValuesMap.count(op.operand1) > 0 &&
                 wireValuesMap.count(op.operand2) > 0) {
        wireValuesMap[op.wire] =
            std::stoi(op.operand1) & std::stoi(op.operand2);
      }

    } else if (op.oper == "LSHIFT") {
      if (isStringDigits(op.operand1) && isStringDigits(op.operand2)) {
        wireValuesMap[op.wire] = std::stoi(op.operand1)
                                 << std::stoi(op.operand2);
      } else if (isStringDigits(op.operand1) &&
                 wireValuesMap.count(op.operand2) > 0) {
        wireValuesMap[op.wire] = std::stoi(op.operand1)
                                 << wireValuesMap[op.operand2];
      } else if (isStringDigits(op.operand2) &&
                 wireValuesMap.count(op.operand1) > 0) {
        wireValuesMap[op.wire] = std::stoi(op.operand2)
                                 << wireValuesMap[op.operand1];
      } else if (wireValuesMap.count(op.operand1) > 0 &&
                 wireValuesMap.count(op.operand2) > 0) {
        wireValuesMap[op.wire] = std::stoi(op.operand1)
                                 << std::stoi(op.operand2);
      }

    } else if (op.operand2.empty() && op.oper.empty()) {
      wireValuesMap[op.wire] = std::stoi(op.operand1);
    }
  }

  std::cout << wireValuesMap["b"];
  return EXIT_SUCCESS;
}
