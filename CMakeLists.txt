cmake_minimum_required(VERSION 3.15)
project(NBodySim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SRC_FILESs
    src/*.cpp
)

# Find SFML version 3.0 or newer 
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

add_executable(NBodySim ${SRC_FILES})

target_link_libraries(NBodySim
    SFML::Graphics
    SFML::Window
    SFML::System
)

