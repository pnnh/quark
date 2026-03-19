#===========================测试相关开始============================

# ---- 统一查找所有依赖 ----
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Boost COMPONENTS system thread chrono filesystem url REQUIRED)
find_package(cmark CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(inja CONFIG REQUIRED)
find_package(libenvpp CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)

# ============================================================
#  QuarkTest — 唯一测试可执行程序
#
#  双模式 main（见 main.cpp）：
#    argv[1] 不以 '-' 开头 → CXXTest 分发模式（兼容 add_test COMMAND）
#    无参数 / --gtest_* 参数  → Google Test 模式
# ============================================================

# 原 CXXTest 的业务测试源文件（不含 string/uuid/basex 子目录）
file(GLOB QuarkTest_SOURCES_ROOT   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB QuarkTest_SOURCES_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/files/*.cpp)
file(GLOB QuarkTest_SOURCES_SQLITE ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/*.cpp)

# GTest 单元测试源文件
set(QuarkTest_GTEST_SOURCES
        string/string_test.cpp
        uuid/uuid_test.cpp
        basex/basex_test.cpp
)

add_executable(QuarkTest
        ${QuarkTest_SOURCES_ROOT}
        ${QuarkTest_SOURCES_FILES}
        ${QuarkTest_SOURCES_SQLITE}
        ${QuarkTest_GTEST_SOURCES}
)
add_dependencies(QuarkTest quark)
target_include_directories(QuarkTest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)
target_link_libraries(QuarkTest PRIVATE
        quark
        GTest::gtest              # 不用 gtest_main：main.cpp 自提供 main()
        unofficial::sqlite3::sqlite3
        spdlog::spdlog
        ${Boost_LIBRARIES}
        cmark::cmark
        yaml-cpp::yaml-cpp
        nlohmann_json::nlohmann_json
        pantor::inja
        libenvpp::libenvpp
        date::date-tz
)

# ---- CTest 注册：原 CXXTest 的四个分发用例（行为不变）----
add_test(NAME TestHelloWorld    COMMAND QuarkTest TestHelloWorld)
add_test(NAME TestSqliteVersion COMMAND QuarkTest TestSqliteVersion)
add_test(NAME TestSqliteSelect  COMMAND QuarkTest TestSqliteSelect)
add_test(NAME TestSelectFiles   COMMAND QuarkTest TestSelectFiles)

# ---- CTest 注册：GTest 用例自动发现 ----
# PRE_TEST：推迟到 ctest 运行时发现，避免构建阶段因 DLL 缺失导致 exe 无法运行
gtest_discover_tests(QuarkTest DISCOVERY_MODE PRE_TEST)

# ---- POST_BUILD：将所有运行时 DLL 复制到 QuarkTest.exe 所在目录 ----
add_custom_command(TARGET QuarkTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:QuarkTest>
        $<TARGET_FILE_DIR:QuarkTest>
        COMMAND_EXPAND_LISTS
)
#===========================测试相关结束===========================
