cmake_minimum_required(VERSION 3.22)

project(TheLinuxProgrammingInterface)

set(ABSL_PROPAGATE_CXX_STD ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)
set(STAGING_DIR ${CMAKE_BINARY_DIR}/depcache)

add_compile_definitions(_FILE_OFFSET_BITS=64)

ExternalProject_Add(spdlog
    PREFIX spdlog
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirds/spdlog
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_INSTALL_PREFIX=${STAGING_DIR}
    -DSPDLOG_BUILD_SHARED=OFF
)

set(ABSL_BUILD_TESTING OFF)
add_subdirectory(thirds/abseil-cpp)

add_subdirectory(thirds/fmt)

add_subdirectory(cha5)