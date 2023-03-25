cmake_minimum_required(VERSION 3.24)
project(invader_v_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(invader_v_01 main.cpp)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(invader_v_01 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

