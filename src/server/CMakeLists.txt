FILE(GLOB SRC "./*.cpp")

add_executable(roflandb ${SRC})
target_include_directories(roflandb PUBLIC inc/)
#target_link_libraries(roflandb PUBLIC keklib)

if (MINGW)
    get_filename_component( Mingw_Path ${CMAKE_CXX_COMPILER} PATH )
    set(MINGW_RUNTIME_LIBS ${Mingw_Path}/libgcc_s_seh-1.dll ${Mingw_Path}/libstdc++-6.dll)
    message(STATUS " - Coping system-libraries: MinGW DLLs.  ${Mingw_Path}")

    add_custom_target(copyDLL)
    foreach(dll  ${MINGW_RUNTIME_LIBS})
        add_custom_command(TARGET copyDLL POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E
                copy ${dll} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()

    add_dependencies(roflandb copyDLL)
endif (MINGW)
