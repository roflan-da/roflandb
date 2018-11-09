FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(query_conditions SHARED ${SRC})
target_include_directories(query_conditions PUBLIC inc)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(query_conditions PUBLIC -g3 -O0 -coverage)
    set_target_properties(query_conditions PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
