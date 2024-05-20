project(Filters)
cmake_minimum_required(VERSION 3.22.1)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(filters.out main.cpp)
target_link_libraries( filters.out ${OpenCV_LIBS} )