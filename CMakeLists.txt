cmake_minimum_required(VERSION 4.2.0)

project(quark VERSION 0.1.0 LANGUAGES C CXX)

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


# 避免警告
if (POLICY CMP0012)
    cmake_policy(SET CMP0012 NEW)
endif ()
# 针对CMake 3.30版本Boost查找相关警告
if (POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif ()
# ============ 收集源文件 ============

# 收集所有源文件
set(QUARK_SOURCES
        hello.cpp
        infra/result/result.cpp
        core/string/string.cpp
)

# 收集所有头文件
set(QUARK_HEADERS
        hello.h
        infra/result/result.h
        core/string/string.h
)


# 创建library目标
add_library(quark SHARED ${QUARK_SOURCES} ${QUARK_HEADERS})

find_package(Boost REQUIRED COMPONENTS url system)
target_link_libraries(quark PUBLIC Boost::url Boost::system)
target_compile_definitions(quark PUBLIC QUARK_HAVE_BOOST)


if (MSVC)
    set_target_properties(quark PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

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
install(FILES hello.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/quark
)

# 递归安装所有模块头文件
install(DIRECTORY
        core/
        infra/
        services/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/quark
        FILES_MATCHING
        PATTERN "*.h"
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

