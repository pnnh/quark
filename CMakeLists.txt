cmake_minimum_required(VERSION 4.2.0)

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

# 收集所有源文件
set(QUARK_SOURCES
        hello.cpp
        infra/result/result.cpp
        infra/collection/list.cpp
        infra/http/http.cpp
        infra/http/query.cpp
        infra/http/url.cpp
        infra/media/image.cpp
        infra/media/json.cpp
        infra/media/mime.cpp
        infra/media/svg.cpp
        infra/utils/basex.cpp
        infra/utils/md5.cpp
        core/graphics/color.cpp
        core/graphics/cube.cpp
        core/graphics/point.cpp
        core/graphics/rectangle.cpp
        core/types/any.cpp
        core/types/bytes.cpp
        core/types/datetime.cpp
        core/types/email.cpp
        core/types/float.cpp
        core/types/integer.cpp
        core/types/regex.cpp
        core/types/size.cpp
        core/string/string.cpp
        services/logger/logger.cpp
        services/random/random.cpp
        services/filesystem/filesystem.cpp
        services/database/sqlite_column.cpp
        services/database/sqlite_command.cpp
        services/database/sqlite_result.cpp
        services/database/sqlite_row.cpp
        services/database/sqlite_service.cpp
)

# 收集所有头文件
set(QUARK_HEADERS
        hello.h
        infra/result/result.h
        infra/collection/list.h
        infra/http/http.h
        infra/http/query.h
        infra/http/url.h
        infra/media/image.h
        infra/media/json.h
        infra/media/mime.h
        infra/media/svg.h
        infra/utils/basex.h
        infra/utils/md5.h
        core/graphics/color.h
        core/graphics/cube.h
        core/graphics/point.h
        core/graphics/rectangle.h
        core/types/any.h
        core/types/bytes.h
        core/types/datetime.h
        core/types/email.h
        core/types/float.h
        core/types/integer.h
        core/types/regex.h
        core/types/size.h
        core/string/string.h
        services/logger/logger.h
        services/random/random.h
        services/filesystem/filesystem.h
        services/database/sqlite_column.h
        services/database/sqlite_command.h
        services/database/sqlite_result.h
        services/database/sqlite_row.h
        services/database/sqlite_service.h
)


# 创建library目标
add_library(quark SHARED ${QUARK_SOURCES} ${QUARK_HEADERS})

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
install(FILES ${QUARK_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/quark
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

