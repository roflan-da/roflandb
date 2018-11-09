FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(commands SHARED ${SRC})
target_include_directories(commands PUBLIC inc)
target_link_libraries(commands PUBLIC table query_conditions)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(commands PUBLIC -g3 -O0 -coverage)
    set_target_properties(commands PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
