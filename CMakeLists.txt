cmake_minimum_required(VERSION 3.29...4.2.3)

project(quark VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置开启显示详细的构建过程
set(CMAKE_VERBOSE_MAKEFILE ON)

# 启用测试
enable_testing()

# 设置开启显示详细的构建过程
set(CMAKE_VERBOSE_MAKEFILE ON)

# 设置标准库位置（便于install使用）
include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
link_directories(${PROJECT_BINARY_DIR})

# 引用头文件导出助手函数
include(GenerateExportHeader)

# 收集所有源文件
set(QUARK_SOURCES
        quark/infra/result/result.cpp
        quark/infra/collection/list.cpp
        quark/infra/http/http.cpp
        quark/infra/http/query.cpp
        quark/infra/http/url.cpp
        quark/infra/media/image.cpp
        quark/infra/media/json.cpp
        quark/infra/media/mime.cpp
        quark/infra/media/svg.cpp
        quark/infra/utils/basex.cpp
        quark/infra/utils/md5.cpp
        quark/core/graphics/color.cpp
        quark/core/graphics/cube.cpp
        quark/core/graphics/point.cpp
        quark/core/graphics/rectangle.cpp
        quark/core/types/any.cpp
        quark/core/types/bytes.cpp
        quark/core/types/datetime.cpp
        quark/core/types/email.cpp
        quark/core/types/float.cpp
        quark/core/types/integer.cpp
        quark/core/types/regex.cpp
        quark/core/types/size.cpp
        quark/core/string/string.cpp
        quark/core/uuid/uuid.cpp
        quark/services/logger/logger.cpp
        quark/services/random/random.cpp
        quark/services/filesystem/filesystem.cpp
        quark/services/database/sqlite_column.cpp
        quark/services/database/sqlite_command.cpp
        quark/services/database/sqlite_result.cpp
        quark/services/database/sqlite_row.cpp
        quark/services/database/sqlite_service.cpp
        quark/services/markdown/MarkdownService.cpp
        quark/services/yaml/yaml.cpp
)

# 收集所有头文件
set(QUARK_HEADERS
        quark/infra/result/result.h
        quark/infra/collection/list.h
        quark/infra/http/http.h
        quark/infra/http/query.h
        quark/infra/http/url.h
        quark/infra/media/image.h
        quark/infra/media/json.h
        quark/infra/media/mime.h
        quark/infra/media/svg.h
        quark/infra/utils/basex.h
        quark/infra/utils/md5.h
        quark/core/graphics/color.h
        quark/core/graphics/cube.h
        quark/core/graphics/point.h
        quark/core/graphics/rectangle.h
        quark/core/types/any.h
        quark/core/types/bytes.h
        quark/core/types/datetime.h
        quark/core/types/email.h
        quark/core/types/float.h
        quark/core/types/integer.h
        quark/core/types/regex.h
        quark/core/types/size.h
        quark/core/string/string.h
        quark/core/uuid/uuid.h
        quark/services/logger/logger.h
        quark/services/random/random.h
        quark/services/filesystem/filesystem.h
        quark/services/database/sqlite_column.h
        quark/services/database/sqlite_command.h
        quark/services/database/sqlite_result.h
        quark/services/database/sqlite_row.h
        quark/services/database/sqlite_service.h
        quark/services/markdown/MarkdownService.h
        quark/services/yaml/yaml.h
)


# 创建library目标
add_library(quark SHARED ${QUARK_SOURCES} ${QUARK_HEADERS})

generate_export_header(quark
        BASE_NAME MTQuark           # 决定生成的宏前缀
        EXPORT_FILE_NAME          # 指定输出路径
        "${CMAKE_CURRENT_SOURCE_DIR}/quark/quark.h"
        EXPORT_MACRO_NAME QKAPI
)

# 让使用方能找到生成的头文件
target_include_directories(quark
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
)

# 查找并引用日志库
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(quark PRIVATE spdlog::spdlog)

# 查找并引用Boost库
find_package(Boost COMPONENTS system thread chrono filesystem url REQUIRED)
target_include_directories(quark PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(quark PRIVATE ${Boost_LIBRARIES})

# 查找并引用Markdown解析库
find_package(cmark CONFIG REQUIRED)
target_link_libraries(quark PRIVATE cmark::cmark)

# 查找并引用Sqlite解析库
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(quark PRIVATE unofficial::sqlite3::sqlite3)

# 查找并引用yaml-cpp解析库
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(quark PRIVATE yaml-cpp::yaml-cpp)

# 查找JSON库
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(quark PRIVATE nlohmann_json::nlohmann_json)

# 查找并链接模板库
find_package(inja CONFIG REQUIRED)
target_link_libraries(quark PRIVATE pantor::inja)

# 查找并引用env解析库
find_package(libenvpp CONFIG REQUIRED)
target_link_libraries(quark PRIVATE libenvpp::libenvpp)

# 查找并引用日期库
find_package(date CONFIG REQUIRED)
target_link_libraries(quark PRIVATE date::date-tz)

# 设置EXPORT目标（必需用于install(EXPORT)）
install(TARGETS quark EXPORT quark-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 设置library的公共头文件目录
target_include_directories(quark PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# 设置library版本和SOVERSION
set_target_properties(quark PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)

# 安装header文件
install(DIRECTORY quark/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/quark
        FILES_MATCHING PATTERN "*.h"
)

# ============ CMake 配置文件安装 ============

# 安装导出的CMake目标配置
install(EXPORT quark-targets
        FILE quark-targets.cmake
        NAMESPACE quark::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/quark
)

# 创建并安装package config文件
include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/quark-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/quark-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/quark
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/quark-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/quark-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/quark-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/quark
)

#===========================测试相关开始============================
add_subdirectory(tests)
## C++动态库测试
#file(GLOB_RECURSE CXXTest_SOURCES tests/*.cpp)
#add_executable(CXXTest ${CXXTest_SOURCES})
#add_dependencies(CXXTest quark)
#target_include_directories(CXXTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(CXXTest PRIVATE quark)
#
## 查找并引用Sqlite解析库
#find_package(unofficial-sqlite3 CONFIG REQUIRED)
#target_link_libraries(CXXTest PRIVATE unofficial::sqlite3::sqlite3)
#
#add_test(NAME CXXTestHelloWorld COMMAND CXXTest TestHelloWorld)
#add_test(NAME CXXTestSqliteVersion COMMAND CXXTest TestSqliteVersion)
#
## C动态库测试
#file(GLOB_RECURSE CTest_SOURCES tests/*.c)
#add_executable(CTest ${CTest_SOURCES})
#add_dependencies(CTest quark)
#target_include_directories(CTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(CTest PRIVATE quark)
#===========================测试相关结束============================