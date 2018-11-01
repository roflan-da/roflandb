FILE(GLOB SRC "./*.cpp")

add_library(commands SHARED ${SRC})

target_include_directories(commands PUBLIC inc)
