FILE(GLOB SRC "./*.cpp")

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

SET(LIBS storage_engine commands parser)

add_executable(roflandb ${SRC})
target_include_directories(roflandb PUBLIC inc/)
target_link_libraries(roflandb PUBLIC ${LIBS})

add_library(roflandb_testlib SHARED ${SRC})
target_include_directories(roflandb_testlib PUBLIC inc/)
target_link_libraries(roflandb_testlib PUBLIC ${LIBS})

if (MINGW)
    get_filename_component( Mingw_Path ${CMAKE_CXX_COMPILER} PATH )
    set(MINGW_RUNTIME_LIBS ${Mingw_Path}/libgcc_s_seh-1.dll ${Mingw_Path}/libstdc++-6.dll)
#    message(STATUS " - Coping system-libraries: MinGW DLLs.  ${Mingw_Path}")

    add_custom_target(copyDLL)
    foreach(dll  ${MINGW_RUNTIME_LIBS})
        add_custom_command(TARGET copyDLL POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E
                copy ${dll} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()

    add_dependencies(roflandb copyDLL)
endif (MINGW)


if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    target_compile_options(roflandb PUBLIC -g3 -O0 -coverage)
    set_target_properties(roflandb PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")

    target_compile_options(roflandb_testlib PUBLIC -g3 -O0 -coverage)
    set_target_properties(roflandb_testlib PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
endif()
