cmake_minimum_required(VERSION 3.0.0)
project(wedit)

target_include_directories(wedit "include/")

set(SOURCES file.cpp file2.cpp ${YOUR_DIRECTORY}/file1.h ${YOUR_DIRECTORY}/file2.h)

add_executable(test ${SOURCES})

add_executable(wedit-app apps/app.cc)
add_executable(wedit-server apps/server.cc)

target_link_libraries(wedit-app ${Boost_LIBRARIES})
target_link_libraries(wedit-server ${Boost_LIBRARIES})