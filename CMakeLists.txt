cmake_minimum_required(VERSION 3.29...4.2.3)

project(quark VERSION 0.1.0 LANGUAGES C CXX)

# 设置开启显示详细的构建过程
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
link_directories(${PROJECT_BINARY_DIR})

add_library(quark hello.cpp hello.h)


