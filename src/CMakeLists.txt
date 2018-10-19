#SET(TARGET_NAME, "roflandb")



FILE(GLOB SRC "./*.cpp")


add_executable(roflandb ${SRC})
target_include_directories(roflandb PRIVATE inc/)
target_include_directories(roflandb PRIVATE ../lib/inc)
target_link_libraries(roflandb PUBLIC keklib)

set_target_properties(roflandb PROPERTIES LINK_FLAGS "${LINK_FLAGS}  -static-libgcc -static-libstdc++")

