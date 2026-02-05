cmake_minimum_required(VERSION 3.10)
project(02_random_walk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point to the local SFML installation
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SFML-3.0.2/install")

set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(02_random_walk random_walk.cc)

target_link_libraries(02_random_walk PRIVATE SFML::Graphics)
