FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(storage_engine SHARED ${SRC})
target_include_directories(storage_engine PUBLIC inc ${Boost_INCLUDE_DIRS})
target_link_libraries(storage_engine ${Boost_LIBRARIES} query_conditions)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(storage_engine PUBLIC -g3 -O0 -coverage)
    set_target_properties(storage_engine PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()

