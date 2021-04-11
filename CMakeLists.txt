cmake_minimum_required(VERSION 3.1)
project(kh_rpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(ENABLE_SSL OFF)

if (ENABLE_SSL)
    add_definitions(-DCINATRA_ENABLE_SSL)
    message(STATUS "Use SSL")
endif()

file(GLOB MAIN_FILE *.cpp)
file(GLOB SRC_FILE ./src/*.cpp)

set(ALL_FILE ${MAIN_FILE} ${SRC_FILE})
add_executable(${PROJECT_NAME} ${ALL_FILE})