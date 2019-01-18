FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

get_property(roflandb_include_dir TARGET roflandb PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

add_executable(tests ${SRC} functional_tests.cpp validator_tests.cpp)
target_link_libraries(tests PUBLIC roflandb_testlib storage_engine commands ${Boost_LIBRARIES})
target_include_directories(tests PUBLIC  inc ${roflandb_include_dir} ${Boost_INCLUDE_DIRS})

if(WIN32)
    target_link_libraries(tests PUBLIC wsock32 ws2_32)
endif()

if (UNIX)
    find_package(Threads)
    target_link_libraries(test PUBLIC ${CMAKE_THREAD_LIBS_INIT} )
endif(UNIX)

