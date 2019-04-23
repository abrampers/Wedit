cmake_minimum_required(VERSION 3.0.0)
project(wedit)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

add_executable(wedit-app apps/app.cc)
add_executable(wedit-server apps/server.cc)

target_link_libraries(wedit-app ${Boost_LIBRARIES})
target_link_libraries(wedit-server ${Boost_LIBRARIES})