FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(commands SHARED ${SRC})

target_include_directories(commands PUBLIC inc)
target_link_libraries(commands PUBLIC table query_conditions)
