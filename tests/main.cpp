//
// Created by Larry on 3/19/2026.
//

#include <filesystem>
#include <iostream>
#include <ostream>

#include "cases.h"

int main(int argc, char *argv[]) {
  std::cout << "Hello, World!" << std::endl;

  std::cout << "current path: " << std::filesystem::current_path() << std::endl;

  printf("arguments: %d,%s\n", argc, argv[1]);
  if (argc > 1) {
    std::string caseName = argv[1];

    std::cout << "selected case: " << caseName << " " << caseName << std::endl;

    auto caseResult = quark::tests::runCase(caseName);
    if (caseResult >= 0) {
      return 0;
    }
  }
}
