cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Grec0 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# Add the executable
add_executable(Grec0 src/main.cpp src/uci.cpp)
