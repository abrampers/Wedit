cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 11)
project(wedit)

include_directories(include/wedit)

add_library(wedit_lib STATIC
    src/crdt.cc
    src/item.cc
    src/uid.cc
    src/utils.cc
    src/Peer.cc
)

add_executable(wedit apps/app.cc)
target_link_libraries(
    wedit
    wedit_lib
)

add_executable(wedit_server apps/server.cc)

add_executable(wedit_peer_test_1 apps/server_test_1.cc)
target_link_libraries(
    wedit_peer_test_1
    wedit_lib
)

add_executable(wedit_peer_test_2 apps/server_test_2.cc)
target_link_libraries(
    wedit_peer_test_2
    wedit_lib
)