cmake_minimum_required(VERSION 3.15)
project(Sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES
    src/*.cpp
)

# Optionally allow user to specify SFML path
if(CMAKE_PREFIX_PATH)
  message(STATUS "Using user-specified CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
else()
  message(STATUS "No CMAKE_PREFIX_PATH specified, using default find_package behavior.")
endif()

# Try to find SFML 3.0 with required components
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

add_executable(Sim ${SOURCES})

target_link_libraries(Sim
    SFML::Graphics
    SFML::Window
    SFML::System
)
