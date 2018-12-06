FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

get_property(roflandb_include_dir TARGET roflandb PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

add_executable(tests ${SRC} functional_tests.cpp validator_tests.cpp)
target_link_libraries(tests roflandb_testlib storage_engine commands)

target_include_directories(tests PUBLIC inc ${roflandb_include_dir})
