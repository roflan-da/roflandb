cmake_minimum_required(VERSION 3.13)
project(roflandb)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)

if (MINGW)
    set(Boost_DEBUG ON)
    set(Boost_USE_STATIC_LIBS OFF) # only find static libs
    set(BOOST_INCLUDEDIR ${PROJECT_SOURCE_DIR}/boost/)
    set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/boost/boost)
    set(BOOST_LIBRARYDIR ${PROJECT_SOURCE_DIR}/boost/lib)
    set(Boost_ARCHITECTURE -x64)
endif (MINGW)

find_package(Boost REQUIRED COMPONENTS filesystem system)

add_subdirectory(src)
add_subdirectory(tests)
