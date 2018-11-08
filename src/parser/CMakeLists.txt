#FILE(GLOB SRC "./*.cpp")
SET(SRC driver.cpp parser.cc scanner.cc)

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(parser SHARED ${SRC})
#add_executable(parser_exe ${SRC})

target_include_directories(parser PUBLIC ".")
#target_include_directories(parser_exe PUBLIC ".")
#target_include_directories(parser_exe PUBLIC inc)
target_link_libraries(parser PUBLIC commands)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(parser PUBLIC -g3 -O0 -coverage)
    set_target_properties(parser PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
