cmake_minimum_required(VERSION 3.10)
project(03_sprite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point to the local SFML installation
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SFML-3.0.2/install")

set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(03_sprite main.cc background.cc)

target_link_libraries(03_sprite PRIVATE SFML::Graphics)

# Copy the background image to the build directory
add_custom_command(TARGET 03_sprite POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/background.jpg"
        $<TARGET_FILE_DIR:03_sprite>)
