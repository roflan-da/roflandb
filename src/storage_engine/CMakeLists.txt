set(Boost_ARCHITECTURE -x64)
#if (MINGW)
    set(Boost_DEBUG ON)
#    set(Boost_USE_STATIC_LIBS        ON) # only find static libs
    set(BOOST_INCLUDEDIR C:/Users/Alexey/Desktop/boost_1_68_0)
#    set(BOOST_ROOT C:/Users/Alexey/Desktop/boost_1_68_0/boost)
    set(BOOST_LIBRARYDIR "C:\\Users\\Alexey\\Desktop\\boost_1_68_0\\stage\\lib")
    set(Boost_ARCHITECTURE -x64)
#endif (MINGW)


find_package(Boost REQUIRED COMPONENTS filesystem system)
message("${Boost_LIBRARIES} as" WARNING)
FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

add_library(storage_engine SHARED ${SRC})
target_include_directories(storage_engine PUBLIC inc ${Boost_INCLUDE_DIRS})
target_link_libraries(storage_engine ${Boost_LIBRARIES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(storage_engine PUBLIC -g3 -O0 -coverage)
    set_target_properties(storage_engine PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()

