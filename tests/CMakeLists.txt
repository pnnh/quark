
#===========================测试相关开始============================
# C++动态库测试
# 注意：不使用 GLOB_RECURSE，避免将 string/string_test.cpp（含gtest头）误收入 CXXTest
file(GLOB CXXTest_SOURCES_ROOT   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB CXXTest_SOURCES_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/files/*.cpp)
file(GLOB CXXTest_SOURCES_SQLITE ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/*.cpp)
set(CXXTest_SOURCES ${CXXTest_SOURCES_ROOT} ${CXXTest_SOURCES_FILES} ${CXXTest_SOURCES_SQLITE})
add_executable(CXXTest ${CXXTest_SOURCES})
add_dependencies(CXXTest quark)
target_include_directories(CXXTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CXXTest PRIVATE quark)

# 查找并引用Sqlite解析库
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE unofficial::sqlite3::sqlite3)

# 查找并引用日志库
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE spdlog::spdlog)

# 查找并引用Boost库
find_package(Boost COMPONENTS system thread chrono filesystem url REQUIRED)
target_include_directories(CXXTest PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(CXXTest PRIVATE ${Boost_LIBRARIES})

# 查找并引用Markdown解析库
find_package(cmark CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE cmark::cmark)

# 查找并引用Sqlite解析库
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE unofficial::sqlite3::sqlite3)

# 查找并引用yaml-cpp解析库
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE yaml-cpp::yaml-cpp)

# 查找JSON库
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE nlohmann_json::nlohmann_json)

# 查找并链接模板库
find_package(inja CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE pantor::inja)

# 查找并引用env解析库
find_package(libenvpp CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE libenvpp::libenvpp)

# 查找并引用日期库
find_package(date CONFIG REQUIRED)
target_link_libraries(CXXTest PRIVATE date::date-tz)

add_test(NAME TestHelloWorld COMMAND CXXTest TestHelloWorld)
add_test(NAME TestSqliteVersion COMMAND CXXTest TestSqliteVersion)
add_test(NAME TestSqliteSelect COMMAND CXXTest TestSqliteSelect)
add_test(NAME TestSelectFiles COMMAND CXXTest TestSelectFiles)

# 将所有运行时依赖DLL（含quark.dll及vcpkg第三方DLL）复制到CXXTest.exe所在目录
# 解决Windows下ctest找不到DLL的问题（quark.dll输出在父级build目录，与CXXTest.exe不同目录）
add_custom_command(TARGET CXXTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:CXXTest>
        $<TARGET_FILE_DIR:CXXTest>
        COMMAND_EXPAND_LISTS
)

# ============================================================
#  StringTest — Google Test 单元测试（string.h C 与 C++ 接口）
# ============================================================
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(StringTest string/string_test.cpp)
add_dependencies(StringTest quark)
target_include_directories(StringTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(StringTest PRIVATE quark GTest::gtest GTest::gtest_main)

# 自动将所有 TEST() 注册为独立的 CTest 测试项
# PRE_TEST: 推迟到 ctest 运行时发现测试，避免构建阶段因 DLL 缺失导致 exe 无法运行
gtest_discover_tests(StringTest DISCOVERY_MODE PRE_TEST)

# 复制运行时 DLL 到 StringTest.exe 所在目录（与 CXXTest 同理）
add_custom_command(TARGET StringTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:StringTest>
        $<TARGET_FILE_DIR:StringTest>
        COMMAND_EXPAND_LISTS
)
#===========================测试相关结束===========================
