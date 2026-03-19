//
// Created by Larry on 3/19/2026.
//

#include <filesystem>
#include <iostream>
#include <gtest/gtest.h>

#include "cases.h"

int main(int argc, char *argv[]) {
  // 若第一个参数不以 '-' 开头，视为 CXXTest 用例名称
  // 兼容 add_test(COMMAND QuarkTest <CaseName>) 的调用方式
  if (argc > 1 && argv[1][0] != '-') {
    std::cout << "current path: " << std::filesystem::current_path() << "\n";
    const std::string caseName = argv[1];
    std::cout << "selected case: " << caseName << "\n";
    const int result = quark::tests::runCase(caseName);
    return result >= 0 ? 0 : 1;
  }

  // 否则交由 Google Test 处理
  // （支持 --gtest_filter、--gtest_list_tests、--gtest_also_run_disabled_tests 等）
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
