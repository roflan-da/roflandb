FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(query_conditions SHARED ${SRC})

target_include_directories(query_conditions PUBLIC inc)
