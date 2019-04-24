cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 11)
project(wedit)

include_directories(include/wedit)

add_library(wedit_lib STATIC 
    src/crdt.cc
    src/item.cc
    src/uid.cc
)

add_executable(wedit apps/app.cc)
target_link_libraries(
    wedit
    wedit_lib
)