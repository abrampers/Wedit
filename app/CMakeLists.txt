cmake_minimum_required(VERSION 3.0.0)
project(wedit-app)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

add_executable(client src/client.cpp)
add_executable(server src/server.cpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(server ${Boost_LIBRARIES})