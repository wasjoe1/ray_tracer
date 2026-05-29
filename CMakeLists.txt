cmake_minimum_required(VERSION 3.20)

project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RayTracer src/main.cpp)

# create compile_commands.json(compilation database) in build folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)