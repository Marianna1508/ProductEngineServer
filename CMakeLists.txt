cmake_minimum_required(VERSION 3.7.2)

project(custom_server
  LANGUAGES C CXX
)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall")

add_subdirectory(src)
