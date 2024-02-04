cmake_minimum_required(VERSION 3.16)
project(PnC LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable (
 PnC
 src/main.cpp
)

add_subdirectory(src/draw)

target_link_libraries(PnC PUBLIC sfml-graphics Draw)
target_link_libraries(Draw sfml-graphics)
target_compile_features(PnC PRIVATE cxx_std_17)

install(TARGETS PnC)