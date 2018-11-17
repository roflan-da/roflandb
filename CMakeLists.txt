cmake_minimum_required(VERSION 3.13)
project(roflandb)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)

if (MINGW)
    set(Boost_DEBUG ON)
    # set(Boost_USE_STATIC_LIBS        ON) # only find static libs
    set(BOOST_INCLUDEDIR C:/Users/Alexey/Desktop/boost_1_68_0)
    # set(BOOST_ROOT C:/Users/Alexey/Desktop/boost_1_68_0/boost)
    set(BOOST_LIBRARYDIR C:/Users/Alexey/Desktop/boost_1_68_0/stage/lib)
    set(Boost_ARCHITECTURE -x64)
endif (MINGW)


find_package(Boost REQUIRED COMPONENTS filesystem system)
message("${Boost_LIBRARIES} as" WARNING)

add_subdirectory(src)
add_subdirectory(tests)
