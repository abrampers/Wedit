cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 11)
project(wedit)

include_directories(include/wedit)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Populate a CMake variable with the sources
set(Wedit_SRCS
    apps/Wedit/mainwindow.ui
    apps/Wedit/mainwindow.cpp
    apps/Wedit/main.cpp
)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

add_library(wedit_lib STATIC
    src/crdt.cc
    src/item.cc
    src/uid.cc
    src/utils.cc
    src/Peer.cc
)

# Tell CMake to create the helloworld executable
add_executable(wedit WIN32 ${Wedit_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(
    wedit 
    Qt5::Widgets
    wedit_lib
)

add_executable(cdrt apps/app.cc)
target_link_libraries(
    cdrt
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