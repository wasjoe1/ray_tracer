# whenever changes are made, CMakeTools extension will run cmake --presets presets
cmake_minimum_required(VERSION 3.20)

project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create executable
add_executable(RayTracer src/main.cpp src/color.cpp) # compiles both the main.cpp & color.cpp & links them into 1 executable RayTracer