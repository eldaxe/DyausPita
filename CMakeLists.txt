cmake_minimum_required(VERSION 3.20)
project(DyausPita VERSION 0.1.0 LANGUAGES CXX)

# PortableKit is pinned as a git submodule; do not vendor a second runtime copy.
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/portablekit/CMakeLists.txt")
    message(FATAL_ERROR "PortableKit submodule is missing. Run: git submodule update --init --recursive")
endif()

add_subdirectory(portablekit)

portablekit_add_game(DyausPitaNative
    PROFILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    SOURCES host/ge2_profile.cpp)
