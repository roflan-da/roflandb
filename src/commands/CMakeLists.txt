FILE(GLOB SRC "./*.cpp")

add_library(commands SHARED ${SRC} SQLStatement.cpp inc/SQLStatement.h)

target_include_directories(commands PUBLIC inc)
