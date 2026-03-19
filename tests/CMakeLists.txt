
#===========================测试相关开始============================
# C++动态库测试
file(GLOB_RECURSE CXXTest_SOURCES ./*.cpp)
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


add_test(NAME CXXTestHelloWorld COMMAND CXXTest TestHelloWorld)
add_test(NAME CXXTestSqliteVersion COMMAND CXXTest TestSqliteVersion)

# C动态库测试
file(GLOB_RECURSE CTest_SOURCES ./*.c)
add_executable(CTest ${CTest_SOURCES})
add_dependencies(CTest quark)
target_include_directories(CTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CTest PRIVATE quark)
#===========================测试相关结束============================