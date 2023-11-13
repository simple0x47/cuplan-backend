cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CROW_ENABLE_SSL ON)

project(cuplan)

add_subdirectory(src)
add_subdirectory(tests)