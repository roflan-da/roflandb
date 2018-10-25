FILE(GLOB SRC "./*.cpp")

get_property(roflandb_include_dir TARGET roflandb PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

add_executable(tests ${SRC})

target_include_directories(tests PUBLIC inc ${roflandb_include_dir})
