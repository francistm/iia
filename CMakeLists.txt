# CMakeList.txt : CMake project for cpq-logviewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)
project (iia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

enable_testing()
add_subdirectory(src)
