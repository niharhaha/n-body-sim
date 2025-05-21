cmake_minimum_required(VERSION 3.15)
project(NBodySim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES
    src/*.cpp
)

# User must specify SFML path at cmake invocation
if(NOT DEFINED CMAKE_PREFIX_PATH)
  message(FATAL_ERROR "You must specify -DCMAKE_PREFIX_PATH to SFML directory")
endif()

# Find SFML version 3.0  
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

add_executable(NBodySim ${SOURCES})

target_link_libraries(NBodySim
    SFML::Graphics
    SFML::Window
    SFML::System
)