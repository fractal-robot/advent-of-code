// flags -lssl -lcrypto for compilation
//
// damn this one is really outdated

#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <string>

std::string md5(const std::string &input) {
  MD5_CTX md5Context;
  MD5_Init(&md5Context);
  MD5_Update(&md5Context, input.c_str(), input.length());

  unsigned char result[MD5_DIGEST_LENGTH];
  MD5_Final(result, &md5Context);

  std::stringstream md5string;
  for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
    md5string << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(result[i]);
  }

  return md5string.str();
}

int main() {

  int counter{};
  std::string puzzleInput = "pqrstuv";

  while (true) {

    std::string input{puzzleInput + std::to_string(counter)};
    std::string hashed = md5(input);

    for (std::size_t i{0}; i <= 5; i++) {
      if (hashed[i] == 0) {
        ++counter;
      }
    }

    if (counter == 5) {
      std::cout << hashed;
      return EXIT_SUCCESS;
    }

    ++counter;
  }

  return 0;
}
