FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(table SHARED ${SRC})
target_include_directories(table PUBLIC inc)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(table PUBLIC -g3 -O0 -coverage)
    set_target_properties(table PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
