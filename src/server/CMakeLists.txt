FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

SET(LIBS storage_engine commands parser)

add_executable(roflandb ${SRC})
#target_link_libraries(roflandb PUBLIC ${LIBS})


add_library(roflandb_testlib SHARED ${SRC})

if(WIN32)
    target_link_libraries(roflandb PUBLIC wsock32 ws2_32)
    target_link_libraries(roflandb_testlib PUBLIC wsock32 ws2_32)
endif()

if (MINGW)
    get_filename_component( Mingw_Path ${CMAKE_CXX_COMPILER} PATH )
    set(MINGW_RUNTIME_LIBS
            ${Mingw_Path}/libgcc_s_seh-1.dll
            ${Mingw_Path}/libstdc++-6.dll
            ${Mingw_Path}/libwinpthread-1.dll)

#    message(STATUS " - Coping system-libraries: MinGW DLLs.  ${Mingw_Path}")

    add_custom_target(copyDLL)
    foreach(dll  ${MINGW_RUNTIME_LIBS})
        add_custom_command(TARGET copyDLL POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E
                copy ${dll} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()

endif (MINGW)

if (UNIX)
    find_package(Threads)
    target_link_libraries(roflandb_testlib PUBLIC ${CMAKE_THREAD_LIBS_INIT} )
    target_link_libraries(roflandb PUBLIC ${CMAKE_THREAD_LIBS_INIT} )
endif(UNIX)

target_include_directories(roflandb PUBLIC inc/)
target_link_libraries(roflandb PUBLIC storage_engine commands parser ${Boost_LIBRARIES})

target_include_directories(roflandb_testlib PUBLIC inc/)
target_link_libraries(roflandb_testlib PUBLIC ${LIBS} ${Boost_LIBRARIES})


if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(roflandb PUBLIC -g3 -O0 -coverage)
    set_target_properties(roflandb PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")

    target_compile_options(roflandb_testlib PUBLIC -g3 -O0 -coverage)
    set_target_properties(roflandb_testlib PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
