cmake_minimum_required(VERSION 3.1)
project(kh_rpc_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

find_package(Boost COMPONENTS system filesystem REQUIRED)

set(ENABLE_SSL OFF)

if (ENABLE_SSL)
    add_definitions(-DCINATRA_ENABLE_SSL)
    message(STATUS "Use SSL")
endif()
include_directories(
        "/usr/local/include"
        "${CMAKE_SOURCE_DIR}/source"
        "${CMAKE_SOURCE_DIR}/source/third_party")
        
file(GLOB MAIN_FILE *.cpp)
file(GLOB SRC_FILE ./src/*.cpp)

set(ALL_FILE ${MAIN_FILE} ${SRC_FILE})
add_executable(${PROJECT_NAME} ${ALL_FILE})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -lssl -lcrypto -lpthread)