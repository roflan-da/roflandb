FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_executable(roflanclient ${SRC})

if(WIN32)
    target_link_libraries(roflanclient PUBLIC wsock32 ws2_32)
endif()

if (UNIX)
    find_package(Threads)
    target_link_libraries(roflanclient PUBLIC ${CMAKE_THREAD_LIBS_INIT} )
endif(UNIX)


target_include_directories(roflanclient PUBLIC inc)
target_link_libraries(roflanclient PUBLIC ${Boost_LIBRARIES})
target_include_directories(roflanclient PUBLIC inc ${Boost_INCLUDE_DIRS})


if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(query_conditions PUBLIC -g3 -O0 -coverage)
    set_target_properties(query_conditions PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
