cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_NAME "dsock")
project(${APP_NAME})

find_package(Qt5Core)

file(GLOB_RECURSE SRC_CPP ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_H ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
add_executable(${APP_NAME} ${SRC_CPP} ${SRC_H})


target_link_libraries(${APP_NAME} Qt5::Core)
