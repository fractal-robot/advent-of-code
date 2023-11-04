#include <array>
#include <iostream>
int main() {

  std::array<int, 4> hello{1, 2, 3, 5};

  std::cout << hello.at(3) << ' ' << hello.at(4);
}
